#ifndef STORE_MODULE_HH
#define STORE_MODULE_HH

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"
#include "mem/port.hh"
#include "mem/request.hh"
#include "params/StoreModule.hh"
#include "sim/eventq.hh"
#include "sim/sim_object.hh"
#include "vta/buffer.hh"
#include "vta/command_queue.hh"
#include "vta/dependency_queue.hh"

using namespace std::literals;

namespace gem5
{

class StoreModule : public SimObject
{
  private:
    RequestorID id;
    bool finish_{};
    Event *finishEvent_;

    class DataPort : public RequestPort
    {
      private:
        StoreModule &owner;

      public:
        DataPort(const std::string_view name, StoreModule &owner) :
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

    CommandQueue &storeCommandQueue;

    DependencyQueue &computeToStoreQueue;
    DependencyQueue &storeToComputeQueue;

    Buffer &outputBuffer;

    class ProcessEvent : public Event
    {
      private:
        StoreModule &owner;

      public:
        ProcessEvent(StoreModule &owner) : owner{owner} {}

        virtual auto process() -> void override {};
    } workingEvent{*this};

  public:
    PARAMS(StoreModule);

    StoreModule(const Params &params) :
        SimObject{params},
        data_port{params.name + ".store_data_port", *this},
        storeCommandQueue{*params.store_command_queue},
        computeToStoreQueue{*params.compute_to_store_queue},
        storeToComputeQueue{*params.store_to_compute_queue},
        outputBuffer{*params.output_buffer}
    {}

    virtual auto
    getPort(const std::string &if_name, PortID idx) -> Port & override
    {
        if (if_name == "store_data_port"sv) {
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
