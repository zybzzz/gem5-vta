#ifndef STORE_MODULE_HH
#define STORE_MODULE_HH

#include "params/StoreModule.hh"
#include "sim/eventq.hh"
#include "sim/sim_object.hh"
#include "vta/buffer.hh"
#include "vta/data_queue.hh"
#include "vta/instruction_queue.hh"
#include "vta/status.hh"
#include "vta/vta.hh"

namespace gem5
{
class StoreModule : public SimObject
{
  private:
    InstructionQueue *storeCommandQueue;

    DataQueue *computeToStoreQueue;
    DataQueue *storeToComputeQueue;

    Buffer *outputBuffer;

    StoreModuleStatus status;

    class StoreModuleWorkingEvent : public Event
    {
      private:
        StoreModule *storeModule;

      public:
        StoreModuleWorkingEvent(StoreModule *storeModule);
        auto process() -> void override;
    };

    StoreModuleWorkingEvent workingEvent;

    vta::Instruction::MemoryInstruction *instruction;

  public:
    PARAMS(StoreModule);

    StoreModule(const Params &params);
};
} // namespace gem5

#endif
