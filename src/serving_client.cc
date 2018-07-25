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
==============================================================================*/

#include <fstream>
#include <iostream>

#include "grpcpp/create_channel.h"
#include "grpcpp/security/credentials.h"
// #include "google/protobuf/map.h"
// #include "tensorflow/core/framework/tensor.h"
#include "generated/prediction_service.grpc.pb.h"
#include "generated/tensor.grpc.pb.h"

using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;

using tensorflow::serving::PredictRequest;
using tensorflow::serving::PredictResponse;
using tensorflow::serving::PredictionService;

typedef google::protobuf::Map<std::string, tensorflow::TensorProto> OutMap;

class ServingClient {
 public:
  ServingClient(std::shared_ptr<Channel> channel)
      : stub_(PredictionService::NewStub(channel)) {}

  std::string callPredict(const std::string& model_name,
                                 const std::string& model_signature_name,
                                 const std::string& file_path) {
    PredictRequest predictRequest;
    PredictResponse response;
    ClientContext context;

    predictRequest.mutable_model_spec()->set_name(model_name);
    predictRequest.mutable_model_spec()->set_signature_name(
        model_signature_name);

    google::protobuf::Map<std::string, tensorflow::TensorProto>& inputs =
        *predictRequest.mutable_inputs();

    tensorflow::TensorProto proto;

    std::ifstream imageFile(file_path, std::ios::binary);

    if (!imageFile.is_open()) {
      std::cout << "Failed to open " << file_path << std::endl;
      return "";
    }

    std::filebuf* pbuf = imageFile.rdbuf();
    auto fileSize = pbuf->pubseekoff(0, std::ios::end, std::ios::in);

    char* image = new char[fileSize]();

    pbuf->pubseekpos(0, std::ios::in);
    pbuf->sgetn(image, fileSize);
    imageFile.close();

    proto.set_dtype(tensorflow::DataType::DT_STRING);
    proto.add_string_val(image, fileSize);

    proto.mutable_tensor_shape()->add_dim()->set_size(1);

    inputs["images"] = proto;

    Status status = stub_->Predict(&context, predictRequest, &response);

    delete[] image;

    if (status.ok()) {
      std::cout << "call predict ok" << std::endl;
      std::cout << "outputs size is " << response.outputs_size() << std::endl;
      OutMap& map_outputs = *response.mutable_outputs();
      OutMap::iterator iter;
      int output_index = 0;

      for (iter = map_outputs.begin(); iter != map_outputs.end(); ++iter) {
        // tensorflow::TensorProto& result_tensor_proto = iter->second;

        // tensorflow::Tensor tensor;
        // bool converted = tensor.FromProto(result_tensor_proto);
        // if (converted) {
        //   std::cout << "the result tensor[" << output_index
        //             << "] is:" << std::endl
        //             << tensor.SummarizeValue(10) << std::endl;
        // } else {
        //   std::cout << "the result tensor[" << output_index
        //             << "] convert failed." << std::endl;
        // }
        
        ++output_index;
      }
      return "Done.";
    } else {
      std::cout << "gRPC call return code: " << status.error_code() << ": "
                << status.error_message() << std::endl;
      return "gRPC failed.";
    }
  }

 private:
  std::unique_ptr<PredictionService::Stub> stub_;
};

int main(int argc, char** argv) {
  std::string server_port = "172.17.0.2:9000";
  std::string image_file = "";
  std::string model_name = "gan";
  std::string model_signature_name = "predict_images";

  ServingClient guide(
      grpc::CreateChannel(server_port, grpc::InsecureChannelCredentials()));
  std::cout << "calling predict using file: " << image_file << "  ..."
            << std::endl;
  std::cout << guide.callPredict(model_name, model_signature_name, image_file)
            << std::endl;
  return 0;
}
