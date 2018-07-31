## C++ client for the TensorFlow prediction service
The repository contains a C++ client of a service that predicts [Street View House Numbers](http://ufldl.stanford.edu/housenumbers/). The client talks to [TensorFlow Serving](https://tensorflow.github.io/serving/) server via gRPC that hosts trained GAN model as described in the [series of articles on Medium](https://towardsdatascience.com/how-to-deploy-machine-learning-models-with-tensorflow-part-1-make-your-model-ready-for-serving-776a14ec3198).  

## Pre-requisities
I have tested the client on Ubuntu 16.04. To build a client code you must install:

- [Protobuf library](https://github.com/google/protobuf) as described [here](https://github.com/google/protobuf/blob/master/src/README.md)
- [GRPC library](https://github.com/grpc/grpc) as described [here](https://github.com/grpc/grpc/blob/master/BUILDING.md)  

The client does not require an installation of the TensorFlow framework.

## Generation of C++ code from protobufs
I have prepared probufs under `./src/protos` and generated C++ headers and sources into `./src/generated`. If you prefer to do that yourself, execute in the terminal following commands:
```
cd <project root>
rm -rf ./src/generated
mkdir ./src/generated
protoc -I ./src/protos --cpp_out=./src/generated --grpc_out=./src/generated --plugin=protoc-gen-grpc=`which grpc_cpp_plugin` ./src/protos/*.proto
```

## Build the client
To build a client, execute the following:
```
make clean
make
```

## Run the client
To test the client locally, first create and run the Docker container with GAN model as described [here](https://towardsdatascience.com/how-to-deploy-machine-learning-models-with-tensorflow-part-2-containerize-it-db0ad7ca35a7) and then execute:
```
./bin/serving_client --server <host address>:<port number> --image_file <path to the image file>
```
For example:
```
./bin/serving_client --server localhost:9000 --image_file ./resources/image_3.jpg
```
