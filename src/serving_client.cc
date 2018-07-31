/* Copyright 2017 Google Inc. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================

Modifications copyright (C) 2018 Vitaly Bezgachev, vitaly.bezgachev@gmail.com

==============================================================================
*/

#include <fstream>
#include <iostream>

#include "grpcpp/create_channel.h"
#include "grpcpp/security/credentials.h"
#include "generated/prediction_service.grpc.pb.h"
#include "generated/tensor.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using tensorflow::serving::PredictRequest;
using tensorflow::serving::PredictResponse;
using tensorflow::serving::PredictionService;

typedef google::protobuf::Map<std::string, tensorflow::TensorProto> OutMap;

/*
Serving client for the prediction service
*/
class ServingClient {

private:
  std::unique_ptr<PredictionService::Stub> stub_;

public:
  // Constructor: create a stub for the prediction service
  ServingClient(std::shared_ptr<Channel> channel) : stub_(PredictionService::NewStub(channel)) {}

  // Call the prediction service
  std::string callPredict(const std::string& model_name,
                          const std::string& model_signature_name,
                          const std::string& file_path) {
    PredictRequest predictRequest;
    PredictResponse response;
    ClientContext context;

    // set model specification: name and signature name
    predictRequest.mutable_model_spec()->set_name(model_name);
    predictRequest.mutable_model_spec()->set_signature_name(model_signature_name);

    // open image file
    std::ifstream imageFile(file_path, std::ios::binary);
    if (!imageFile.is_open()) {
      std::cout << "Failed to open " << file_path << std::endl;
      return "";
    }

    std::filebuf* pbuf = imageFile.rdbuf();
    auto fileSize = pbuf->pubseekoff(0, std::ios::end, std::ios::in);

    // read file content into the memory
    char* image = new char[fileSize]();
    pbuf->pubseekpos(0, std::ios::in);
    pbuf->sgetn(image, fileSize);
    imageFile.close();

    // create input protobuf for the image
    tensorflow::TensorProto proto;
    proto.set_dtype(tensorflow::DataType::DT_STRING);
    proto.add_string_val(image, fileSize);

    proto.mutable_tensor_shape()->add_dim()->set_size(1);

    // initialize prediction service inputs
    google::protobuf::Map<std::string, tensorflow::TensorProto>& inputs = *predictRequest.mutable_inputs();
    inputs["images"] = proto;

    // issue gRPC call to the service
    Status status = stub_->Predict(&context, predictRequest, &response);

    // free the memory
    delete[] image;

    // check the response
    if (status.ok()) {
      std::cout << "call predict ok" << std::endl;
      std::cout << "outputs size is " << response.outputs_size() << std::endl;
      OutMap& map_outputs = *response.mutable_outputs();
      OutMap::iterator iter;
      int output_index = 0;

      // read the response
      for (iter = map_outputs.begin(); iter != map_outputs.end(); ++iter) {
        tensorflow::TensorProto& result_tensor_proto = iter->second;
        std::cout << "number of probabilies " << result_tensor_proto.float_val_size() << std::endl;

        int maxIdx = -1;
        float maxVal = -1;
        for (int i = 0; i < result_tensor_proto.float_val_size(); ++i) {
          float val = result_tensor_proto.float_val(i);
          std::cout << "probability of " << i << " is " << val << std::endl;

          if (maxVal < val) {
            maxVal = val;
            maxIdx = i;
          }
        }

        std::cout << std::endl << "most probably the digit on the image is " << maxIdx << std::endl << std::endl;

        ++output_index;
      }

      return "Done.";
    }
    else {
      std::cout << "gRPC call return code: " << status.error_code() << ": "
                << status.error_message() << std::endl;
      return "gRPC failed.";
    }
  }
};


/*
Application entry point
*/
int main(int argc, char** argv) {
  const std::string model_name = "gan";
  const std::string model_signature_name = "predict_images";

  std::string server = "172.17.0.2:9000";
  std::string image_file = "./resources/Afghan_hound_00116.jpg";

  // parse arguments
  for (int i = 0; i < argc; ++i) {
    if (std::string(argv[i]) == "--server" && i + 1 < argc) {
      server = argv[++i];
    }

    if (std::string(argv[i]) == "--image_file" && i + 1 < argc) {
      image_file = argv[++i];
    }
  }

  std::cout << "calling prediction service on " << server << std::endl;

  // create and call serving client
  ServingClient guide(grpc::CreateChannel(server, grpc::InsecureChannelCredentials()));
  std::cout << "calling predict using file: " << image_file << "  ..." << std::endl;
  std::cout << guide.callPredict(model_name, model_signature_name, image_file) << std::endl;
  return 0;
}
