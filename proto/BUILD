package(default_visibility = ["//visibility:public"])

load("@org_pubref_rules_protobuf//cpp:rules.bzl", "cc_proto_library")

cc_proto_library(
    name = "discovery_server_proto",
    protos = ["discovery.proto"],
    with_grpc = True,
    verbose = 2,
)