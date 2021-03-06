// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: discovery.proto

#include "discovery.pb.h"
#include "discovery.grpc.pb.h"

#include <grpc++/impl/codegen/async_stream.h>
#include <grpc++/impl/codegen/async_unary_call.h>
#include <grpc++/impl/codegen/channel_interface.h>
#include <grpc++/impl/codegen/client_unary_call.h>
#include <grpc++/impl/codegen/method_handler_impl.h>
#include <grpc++/impl/codegen/rpc_service_method.h>
#include <grpc++/impl/codegen/service_type.h>
#include <grpc++/impl/codegen/sync_stream.h>
namespace discovery {

static const char* DiscoveryService_method_names[] = {
  "/discovery.DiscoveryService/RegisterService",
  "/discovery.DiscoveryService/Discover",
  "/discovery.DiscoveryService/ListAllServices",
  "/discovery.DiscoveryService/State",
};

std::unique_ptr< DiscoveryService::Stub> DiscoveryService::NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options) {
  std::unique_ptr< DiscoveryService::Stub> stub(new DiscoveryService::Stub(channel));
  return stub;
}

DiscoveryService::Stub::Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel)
  : channel_(channel), rpcmethod_RegisterService_(DiscoveryService_method_names[0], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_Discover_(DiscoveryService_method_names[1], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_ListAllServices_(DiscoveryService_method_names[2], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  , rpcmethod_State_(DiscoveryService_method_names[3], ::grpc::internal::RpcMethod::NORMAL_RPC, channel)
  {}

::grpc::Status DiscoveryService::Stub::RegisterService(::grpc::ClientContext* context, const ::discovery::RegistryEntry& request, ::discovery::RegistryEntry* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_RegisterService_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::discovery::RegistryEntry>* DiscoveryService::Stub::AsyncRegisterServiceRaw(::grpc::ClientContext* context, const ::discovery::RegistryEntry& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::discovery::RegistryEntry>::Create(channel_.get(), cq, rpcmethod_RegisterService_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::discovery::RegistryEntry>* DiscoveryService::Stub::PrepareAsyncRegisterServiceRaw(::grpc::ClientContext* context, const ::discovery::RegistryEntry& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::discovery::RegistryEntry>::Create(channel_.get(), cq, rpcmethod_RegisterService_, context, request, false);
}

::grpc::Status DiscoveryService::Stub::Discover(::grpc::ClientContext* context, const ::discovery::RegistryEntry& request, ::discovery::RegistryEntry* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_Discover_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::discovery::RegistryEntry>* DiscoveryService::Stub::AsyncDiscoverRaw(::grpc::ClientContext* context, const ::discovery::RegistryEntry& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::discovery::RegistryEntry>::Create(channel_.get(), cq, rpcmethod_Discover_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::discovery::RegistryEntry>* DiscoveryService::Stub::PrepareAsyncDiscoverRaw(::grpc::ClientContext* context, const ::discovery::RegistryEntry& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::discovery::RegistryEntry>::Create(channel_.get(), cq, rpcmethod_Discover_, context, request, false);
}

::grpc::Status DiscoveryService::Stub::ListAllServices(::grpc::ClientContext* context, const ::discovery::Empty& request, ::discovery::ServiceList* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_ListAllServices_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::discovery::ServiceList>* DiscoveryService::Stub::AsyncListAllServicesRaw(::grpc::ClientContext* context, const ::discovery::Empty& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::discovery::ServiceList>::Create(channel_.get(), cq, rpcmethod_ListAllServices_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::discovery::ServiceList>* DiscoveryService::Stub::PrepareAsyncListAllServicesRaw(::grpc::ClientContext* context, const ::discovery::Empty& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::discovery::ServiceList>::Create(channel_.get(), cq, rpcmethod_ListAllServices_, context, request, false);
}

::grpc::Status DiscoveryService::Stub::State(::grpc::ClientContext* context, const ::discovery::StateRequest& request, ::discovery::StateResponse* response) {
  return ::grpc::internal::BlockingUnaryCall(channel_.get(), rpcmethod_State_, context, request, response);
}

::grpc::ClientAsyncResponseReader< ::discovery::StateResponse>* DiscoveryService::Stub::AsyncStateRaw(::grpc::ClientContext* context, const ::discovery::StateRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::discovery::StateResponse>::Create(channel_.get(), cq, rpcmethod_State_, context, request, true);
}

::grpc::ClientAsyncResponseReader< ::discovery::StateResponse>* DiscoveryService::Stub::PrepareAsyncStateRaw(::grpc::ClientContext* context, const ::discovery::StateRequest& request, ::grpc::CompletionQueue* cq) {
  return ::grpc::internal::ClientAsyncResponseReaderFactory< ::discovery::StateResponse>::Create(channel_.get(), cq, rpcmethod_State_, context, request, false);
}

DiscoveryService::Service::Service() {
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DiscoveryService_method_names[0],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DiscoveryService::Service, ::discovery::RegistryEntry, ::discovery::RegistryEntry>(
          std::mem_fn(&DiscoveryService::Service::RegisterService), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DiscoveryService_method_names[1],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DiscoveryService::Service, ::discovery::RegistryEntry, ::discovery::RegistryEntry>(
          std::mem_fn(&DiscoveryService::Service::Discover), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DiscoveryService_method_names[2],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DiscoveryService::Service, ::discovery::Empty, ::discovery::ServiceList>(
          std::mem_fn(&DiscoveryService::Service::ListAllServices), this)));
  AddMethod(new ::grpc::internal::RpcServiceMethod(
      DiscoveryService_method_names[3],
      ::grpc::internal::RpcMethod::NORMAL_RPC,
      new ::grpc::internal::RpcMethodHandler< DiscoveryService::Service, ::discovery::StateRequest, ::discovery::StateResponse>(
          std::mem_fn(&DiscoveryService::Service::State), this)));
}

DiscoveryService::Service::~Service() {
}

::grpc::Status DiscoveryService::Service::RegisterService(::grpc::ServerContext* context, const ::discovery::RegistryEntry* request, ::discovery::RegistryEntry* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DiscoveryService::Service::Discover(::grpc::ServerContext* context, const ::discovery::RegistryEntry* request, ::discovery::RegistryEntry* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DiscoveryService::Service::ListAllServices(::grpc::ServerContext* context, const ::discovery::Empty* request, ::discovery::ServiceList* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}

::grpc::Status DiscoveryService::Service::State(::grpc::ServerContext* context, const ::discovery::StateRequest* request, ::discovery::StateResponse* response) {
  (void) context;
  (void) request;
  (void) response;
  return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
}


}  // namespace discovery

