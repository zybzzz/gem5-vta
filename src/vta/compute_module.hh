#ifndef COMPUTE_MODULE_HH
#define COMPUTE_MODULE_HH

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"
#include "mem/packet.hh"
#include "mem/port.hh"
#include "params/ComputeModule.hh"
#include "sim/sim_object.hh"
#include "vta/buffer.hh"
#include "vta/command_queue.hh"
#include "vta/dependency_queue.hh"

using namespace std::literals;

namespace gem5
{

class ComputeModule : public SimObject
{
  private:
    RequestorID id;
    bool finish_{};
    Event *finishEvent_;

    class MicroOpPort : public RequestPort
    {
      private:
        ComputeModule &owner;

      public:
        MicroOpPort(const std::string_view name, ComputeModule &owner) :
            RequestPort{std::string{name}}, owner{owner}
        {}

      protected:
        virtual auto
        recvTimingResp(PacketPtr pkt) -> bool override
        {
            delete pkt;
            return true;
        }

        virtual auto
        recvReqRetry() -> void override
        {}

        virtual auto
        sendRetryResp() -> void override
        {}
    } micro_op_port;

    class DataPort : public RequestPort
    {
      private:
        ComputeModule &owner;

      public:
        DataPort(const std::string_view name, ComputeModule &owner) :
            RequestPort{std::string{name}}, owner{owner}
        {}

      protected:
        virtual auto
        recvTimingResp(PacketPtr pkt) -> bool override
        {
            delete pkt;
            return true;
        }

        virtual auto
        recvReqRetry() -> void override
        {}

        virtual auto
        sendRetryResp() -> void override
        {}
    } data_port;

    CommandQueue &computeCommandQueue;

    DependencyQueue &loadToComputeQueue;
    DependencyQueue &computeToLoadQueue;
    DependencyQueue &computeToStoreQueue;
    DependencyQueue &storeToComputeQueue;

    Buffer &inputBuffer;
    Buffer &weightBuffer;
    Buffer &outputBuffer;

  public:
    PARAMS(ComputeModule);

    ComputeModule(const Params &params) :
        SimObject{params},
        micro_op_port{params.name + ".micro_op_port", *this},
        data_port{params.name + ".compute_data_port", *this},
        computeCommandQueue{*params.compute_command_queue},
        loadToComputeQueue{*params.load_to_compute_queue},
        computeToLoadQueue{*params.compute_to_load_queue},
        computeToStoreQueue{*params.compute_to_store_queue},
        storeToComputeQueue{*params.store_to_compute_queue},
        inputBuffer{*params.input_buffer},
        weightBuffer{*params.weight_buffer},
        outputBuffer{*params.output_buffer}
    {}

    virtual auto
    getPort(const std::string &if_name, PortID idx) -> Port & override
    {
        if (if_name == "micro_op_port"sv) {
            return micro_op_port;
        }
        if (if_name == "compute_data_port"sv) {
            return data_port;
        }
        return SimObject::getPort(if_name, idx);
    }

    constexpr auto
    requestorId() noexcept -> RequestorID &
    {
        return id;
    }

    constexpr auto
    finish() -> bool &
    {
        return finish_;
    }

    constexpr auto
    finishEvent() noexcept -> Event *&
    {
        return finishEvent_;
    }
};

} // namespace gem5

#endif
