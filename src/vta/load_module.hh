#ifndef LOAD_MODULE_HH
#define LOAD_MODULE_HH

#include "params/LoadModule.hh"
#include "sim/eventq.hh"
#include "sim/sim_object.hh"
#include "vta/buffer.hh"
#include "vta/data_queue.hh"
#include "vta/instruction_queue.hh"
#include "vta/status.hh"

namespace gem5
{
class LoadModule : public SimObject
{
  private:
    InstructionQueue *loadCommandQueue;

    DataQueue *computeToLoadQueue;
    DataQueue *loadToComputeQueue;

    Buffer *inputBuffer;
    Buffer *weightBuffer;

    LoadModuleStatus status;

    class LoadModuleWorkingEvent : public Event
    {
      private:
        LoadModule *loadModule;

      public:
        LoadModuleWorkingEvent(LoadModule *loadModule);
        auto process() -> void override;
    };

    LoadModuleWorkingEvent workingEvent;

    vta::Instruction::MemoryInstruction *instruction;

  public:
    PARAMS(LoadModule);

    LoadModule(const Params &params);
};
} // namespace gem5

#endif
