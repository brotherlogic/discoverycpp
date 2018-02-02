package main

import (
       "log"

"golang.org/x/net/context"
	"google.golang.org/grpc"

pbdi "github.com/brotherlogic/discovery/proto"
)

func main() {

conn, err := grpc.Dial(":50051", grpc.WithInsecure())
      if err != nil {
      	 log.Fatalf("Cannot reach discover server: %v (trying to discover)", err)
	 }
	 defer conn.Close()

	 registry := pbdi.NewDiscoveryServiceClient(conn)
	 r, err := registry.RegisterService(context.Background(), &pbdi.RegistryEntry{Name: "testing", Master: true, Identifier: "madeup", Ip: "192.168.1.1"})

	 if err != nil {
	    log.Fatalf("Failure to list: %v", err)
				}

					log.Printf("HERE = %v\n", r)

}