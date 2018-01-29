#include <string>

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
using discovery::Empty;
using discovery::StateRequest;
using discovery::ServiceList;
using discovery::StateResponse;
using discovery::DiscoveryService;

class DiscoveryImpl final : public DiscoveryService::Service {
 public:
  explicit DiscoveryImpl() {
  }

  Status RegisterService(ServerContext* context, const RegistryEntry* entryIn,
			 RegistryEntry* entryOut) override {
    return Status::CANCELLED;
  }

  Status Discover(ServerContext* context, const RegistryEntry* entryIn,
		  RegistryEntry* entryOut) override {
    return Status::CANCELLED;
  }

  Status ListAllServices(ServerContext* context, const Empty* empty,
			 ServiceList* list) override {
    return Status::CANCELLED;
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
  server->Wait();
}

int main(int argc, char** argv) {
  RunServer();

  return 0;
}
