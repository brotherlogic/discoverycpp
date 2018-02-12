#include <string>
#include <chrono>
#include <thread>

#include <grpc/grpc.h>
#include <grpc++/server.h>
#include <grpc++/server_builder.h>
#include <grpc++/server_context.h>
#include <grpc++/security/server_credentials.h>
#include "proto/discovery.grpc.pb.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using discovery::RegistryEntry;
using discovery::RegisterRequest;
using discovery::RegisterResponse;
using discovery::DiscoverRequest;
using discovery::DiscoverResponse;
using discovery::ListRequest;
using discovery::ListResponse;
using discovery::Empty;
using discovery::StateRequest;
using discovery::ServiceList;
using discovery::StateResponse;
using discovery::DiscoveryService;

class DiscoveryImpl final : public DiscoveryService::Service {
 public:
  std::map<std::string, RegistryEntry*> masterMap;
  std::map<std::string, std::list<RegistryEntry*>> slaveMap;
  std::map<std::string, int> lastPortUsed;
  std::map<int, bool> externalPorts;
  
  explicit DiscoveryImpl() {
    externalPorts[50052] = true;
    externalPorts[50053] = true;
  }

  int getExternalPort() {
    for (std::map<int, bool>::iterator it=externalPorts.begin(); it != externalPorts.end(); ++it)
      if (it->second) {
	externalPorts[it->first] = false;
	return it->first;
      }

    return -1;
  }

  int getInternalPort(std::string identifier) {
    int value = lastPortUsed[identifier];

    if (value == 0) {
      lastPortUsed[identifier] = 50055;
      value = 50055;
    }

    lastPortUsed[identifier]++;
    return value;
  }

  void clean() {
    auto curr_time = static_cast<std::int64_t>(time(0));
    for (std::map<std::string, RegistryEntry*>::iterator it=masterMap.begin(); it != masterMap.end(); ++it) {
      if (curr_time - it->second->last_seen_time() > it->second->time_to_clean()) {
	masterMap.erase(it->second->name());
      }
    }
    
    for (std::map<std::string, std::list<RegistryEntry*>>::iterator it = slaveMap.begin(); it != slaveMap.end(); ++it) {
      for(std::list<RegistryEntry*>::iterator it2 = it->second.begin(); it2 != it->second.end();)
	if (curr_time - (*it2)->last_seen_time() > (*it2)->time_to_clean()) {
	  it->second.erase(it2);
	} else {
	  ++it2;
	}
    }
  }

  void cleanEntries() {
    while (true) {
      this->clean();
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
  }

  Status RegisterService(ServerContext* context, const RegisterRequest* entryIn,
			 RegisterResponse* entryOut) override {
    // This server is already registered - update the last seen time
    if (entryIn->service().port() > 0) {
      if (entryIn->service().master()) {
	RegistryEntry* entry = masterMap[entryIn->service().name()];
	if (entry->ip() == entryIn->service().ip() && entry->port() == entryIn->service().port()) {
	  entry->set_last_seen_time(static_cast<std::int64_t>(time(0)));
	  entryOut->mutable_service()->CopyFrom(*entry);
	  return Status::OK;
	} else {
	  return Status(grpc::INVALID_ARGUMENT, "There is already a master for this service");
	}
      } else {
	std::list<RegistryEntry*> entries = slaveMap[entryIn->service().name()];
	for (RegistryEntry* entry : entries) {
	  if (entry->ip() == entryIn->service().ip() && entry->port() == entryIn->service().port()) {
	    entry->set_last_seen_time(static_cast<std::int64_t>(time(0)));
	    entryOut->mutable_service()->CopyFrom(*entry);
	    return Status::OK;
	  }

	  return Status(grpc::INVALID_ARGUMENT, "Unable to locate this service - please re-register");
	}
      }
    }

    // This server is not registered
    if (entryIn->service().master()) {
      return Status(grpc::INVALID_ARGUMENT, "Unable to register as master");
    }

    int portNumber = entryIn->service().external_port() ? getExternalPort() : getInternalPort(entryIn->service().identifier());

    // Could we acquire a port
    if (portNumber < 0) {
      return Status(grpc::INTERNAL, "Unable to find a free port");
    }

    entryOut->mutable_service()->CopyFrom(entryIn->service());
    entryOut->mutable_service()->set_register_time(static_cast<std::int64_t>(time(0)));
    entryOut->mutable_service()->set_port(portNumber); 

    return Status::OK;
  }

  Status Discover(ServerContext* context, const DiscoverRequest* entryIn,
		  DiscoverResponse* entryOut) override {
    entryOut->mutable_service()->CopyFrom(*masterMap[entryIn->request().name()]);
    if (entryOut) {
      return Status::OK;
    }

    return Status(grpc::INTERNAL, "Unable to locate master");
  }

  Status ListAllServices(ServerContext* context, const ListRequest* empty,
			 ListResponse* list) override {
    for (std::map<std::string, RegistryEntry*>::iterator it=masterMap.begin(); it != masterMap.end(); ++it) {
      RegistryEntry* entry = list->mutable_services()->add_services();
      entry->MergeFrom(*it->second);
    }

    for (std::map<std::string, std::list<RegistryEntry*>>::iterator it = slaveMap.begin(); it != slaveMap.end(); ++it) {
      for(RegistryEntry* entry : it->second) {
	RegistryEntry* tEntry = list->mutable_services()->add_services();
	tEntry->MergeFrom(*entry);
      }
    }

    return Status::OK;
  }

  Status State(ServerContext* context, const StateRequest* request,
	       StateResponse* response) override {
    return Status::CANCELLED;
  }
};

void RunServer() {
  std::string server_address("0.0.0.0:50051");
  DiscoveryImpl service;

  ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);
  std::unique_ptr<Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << server_address << std::endl;

  // Start the cleaner thread
  std::thread cleaner(&DiscoveryImpl::cleanEntries, &service);

  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}
