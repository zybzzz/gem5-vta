#ifndef STORE_MODULE_HH
#define STORE_MODULE_HH

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"
#include "params/StoreModule.hh"
#include "sim/eventq.hh"
#include "sim/sim_object.hh"
#include "vta/buffer.hh"
#include "vta/command_queue.hh"
#include "vta/dependency_queue.hh"

namespace gem5
{

class StoreModule : public SimObject
{
  private:
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
        storeCommandQueue{*params.store_command_queue},
        computeToStoreQueue{*params.compute_to_store_queue},
        storeToComputeQueue{*params.store_to_compute_queue},
        outputBuffer{*params.output_buffer}
    {}
};

} // namespace gem5

#endif
