// Generated by the gRPC C++ plugin.
// If you make any local change, they will be lost.
// source: prediction_service.proto
#ifndef GRPC_prediction_5fservice_2eproto__INCLUDED
#define GRPC_prediction_5fservice_2eproto__INCLUDED

#include "prediction_service.pb.h"

#include <grpcpp/impl/codegen/async_generic_service.h>
#include <grpcpp/impl/codegen/async_stream.h>
#include <grpcpp/impl/codegen/async_unary_call.h>
#include <grpcpp/impl/codegen/method_handler_impl.h>
#include <grpcpp/impl/codegen/proto_utils.h>
#include <grpcpp/impl/codegen/rpc_method.h>
#include <grpcpp/impl/codegen/service_type.h>
#include <grpcpp/impl/codegen/status.h>
#include <grpcpp/impl/codegen/stub_options.h>
#include <grpcpp/impl/codegen/sync_stream.h>

namespace grpc {
class CompletionQueue;
class Channel;
class ServerCompletionQueue;
class ServerContext;
}  // namespace grpc

namespace tensorflow {
namespace serving {

// open source marker; do not remove
// PredictionService provides access to machine-learned models loaded by
// model_servers.
class PredictionService final {
 public:
  static constexpr char const* service_full_name() {
    return "tensorflow.serving.PredictionService";
  }
  class StubInterface {
   public:
    virtual ~StubInterface() {}
    // Predict -- provides access to loaded TensorFlow model.
    virtual ::grpc::Status Predict(::grpc::ClientContext* context, const ::tensorflow::serving::PredictRequest& request, ::tensorflow::serving::PredictResponse* response) = 0;
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::tensorflow::serving::PredictResponse>> AsyncPredict(::grpc::ClientContext* context, const ::tensorflow::serving::PredictRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::tensorflow::serving::PredictResponse>>(AsyncPredictRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::tensorflow::serving::PredictResponse>> PrepareAsyncPredict(::grpc::ClientContext* context, const ::tensorflow::serving::PredictRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReaderInterface< ::tensorflow::serving::PredictResponse>>(PrepareAsyncPredictRaw(context, request, cq));
    }
  private:
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::tensorflow::serving::PredictResponse>* AsyncPredictRaw(::grpc::ClientContext* context, const ::tensorflow::serving::PredictRequest& request, ::grpc::CompletionQueue* cq) = 0;
    virtual ::grpc::ClientAsyncResponseReaderInterface< ::tensorflow::serving::PredictResponse>* PrepareAsyncPredictRaw(::grpc::ClientContext* context, const ::tensorflow::serving::PredictRequest& request, ::grpc::CompletionQueue* cq) = 0;
  };
  class Stub final : public StubInterface {
   public:
    Stub(const std::shared_ptr< ::grpc::ChannelInterface>& channel);
    ::grpc::Status Predict(::grpc::ClientContext* context, const ::tensorflow::serving::PredictRequest& request, ::tensorflow::serving::PredictResponse* response) override;
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::tensorflow::serving::PredictResponse>> AsyncPredict(::grpc::ClientContext* context, const ::tensorflow::serving::PredictRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::tensorflow::serving::PredictResponse>>(AsyncPredictRaw(context, request, cq));
    }
    std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::tensorflow::serving::PredictResponse>> PrepareAsyncPredict(::grpc::ClientContext* context, const ::tensorflow::serving::PredictRequest& request, ::grpc::CompletionQueue* cq) {
      return std::unique_ptr< ::grpc::ClientAsyncResponseReader< ::tensorflow::serving::PredictResponse>>(PrepareAsyncPredictRaw(context, request, cq));
    }

   private:
    std::shared_ptr< ::grpc::ChannelInterface> channel_;
    ::grpc::ClientAsyncResponseReader< ::tensorflow::serving::PredictResponse>* AsyncPredictRaw(::grpc::ClientContext* context, const ::tensorflow::serving::PredictRequest& request, ::grpc::CompletionQueue* cq) override;
    ::grpc::ClientAsyncResponseReader< ::tensorflow::serving::PredictResponse>* PrepareAsyncPredictRaw(::grpc::ClientContext* context, const ::tensorflow::serving::PredictRequest& request, ::grpc::CompletionQueue* cq) override;
    const ::grpc::internal::RpcMethod rpcmethod_Predict_;
  };
  static std::unique_ptr<Stub> NewStub(const std::shared_ptr< ::grpc::ChannelInterface>& channel, const ::grpc::StubOptions& options = ::grpc::StubOptions());

  class Service : public ::grpc::Service {
   public:
    Service();
    virtual ~Service();
    // Predict -- provides access to loaded TensorFlow model.
    virtual ::grpc::Status Predict(::grpc::ServerContext* context, const ::tensorflow::serving::PredictRequest* request, ::tensorflow::serving::PredictResponse* response);
  };
  template <class BaseClass>
  class WithAsyncMethod_Predict : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithAsyncMethod_Predict() {
      ::grpc::Service::MarkMethodAsync(0);
    }
    ~WithAsyncMethod_Predict() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Predict(::grpc::ServerContext* context, const ::tensorflow::serving::PredictRequest* request, ::tensorflow::serving::PredictResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestPredict(::grpc::ServerContext* context, ::tensorflow::serving::PredictRequest* request, ::grpc::ServerAsyncResponseWriter< ::tensorflow::serving::PredictResponse>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  typedef WithAsyncMethod_Predict<Service > AsyncService;
  template <class BaseClass>
  class WithGenericMethod_Predict : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithGenericMethod_Predict() {
      ::grpc::Service::MarkMethodGeneric(0);
    }
    ~WithGenericMethod_Predict() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Predict(::grpc::ServerContext* context, const ::tensorflow::serving::PredictRequest* request, ::tensorflow::serving::PredictResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
  };
  template <class BaseClass>
  class WithRawMethod_Predict : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithRawMethod_Predict() {
      ::grpc::Service::MarkMethodRaw(0);
    }
    ~WithRawMethod_Predict() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable synchronous version of this method
    ::grpc::Status Predict(::grpc::ServerContext* context, const ::tensorflow::serving::PredictRequest* request, ::tensorflow::serving::PredictResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    void RequestPredict(::grpc::ServerContext* context, ::grpc::ByteBuffer* request, ::grpc::ServerAsyncResponseWriter< ::grpc::ByteBuffer>* response, ::grpc::CompletionQueue* new_call_cq, ::grpc::ServerCompletionQueue* notification_cq, void *tag) {
      ::grpc::Service::RequestAsyncUnary(0, context, request, response, new_call_cq, notification_cq, tag);
    }
  };
  template <class BaseClass>
  class WithStreamedUnaryMethod_Predict : public BaseClass {
   private:
    void BaseClassMustBeDerivedFromService(const Service *service) {}
   public:
    WithStreamedUnaryMethod_Predict() {
      ::grpc::Service::MarkMethodStreamed(0,
        new ::grpc::internal::StreamedUnaryHandler< ::tensorflow::serving::PredictRequest, ::tensorflow::serving::PredictResponse>(std::bind(&WithStreamedUnaryMethod_Predict<BaseClass>::StreamedPredict, this, std::placeholders::_1, std::placeholders::_2)));
    }
    ~WithStreamedUnaryMethod_Predict() override {
      BaseClassMustBeDerivedFromService(this);
    }
    // disable regular version of this method
    ::grpc::Status Predict(::grpc::ServerContext* context, const ::tensorflow::serving::PredictRequest* request, ::tensorflow::serving::PredictResponse* response) override {
      abort();
      return ::grpc::Status(::grpc::StatusCode::UNIMPLEMENTED, "");
    }
    // replace default version of method with streamed unary
    virtual ::grpc::Status StreamedPredict(::grpc::ServerContext* context, ::grpc::ServerUnaryStreamer< ::tensorflow::serving::PredictRequest,::tensorflow::serving::PredictResponse>* server_unary_streamer) = 0;
  };
  typedef WithStreamedUnaryMethod_Predict<Service > StreamedUnaryService;
  typedef Service SplitStreamedService;
  typedef WithStreamedUnaryMethod_Predict<Service > StreamedService;
};

}  // namespace serving
}  // namespace tensorflow


#endif  // GRPC_prediction_5fservice_2eproto__INCLUDED
