#ifndef COMPUTE_MODULE_HH
#define COMPUTE_MODULE_HH

#include "params/ComputeModule.hh"
#include "sim/eventq.hh"
#include "sim/sim_object.hh"
#include "vta/buffer.hh"
#include "vta/data_queue.hh"
#include "vta/instruction_queue.hh"
#include "vta/status.hh"

namespace gem5
{
class ComputeModule : public SimObject
{
  private:
    using InstructionType = vta::Instruction::InstructionType;
    InstructionQueue *computeCommandQueue;

    DataQueue *computeToStoreQueue;
    DataQueue *storeToComputeQueue;
    DataQueue *computeToLoadQueue;
    DataQueue *loadToComputeQueue;

    Buffer *inputBuffer;
    Buffer *weightBuffer;
    Buffer *outputBuffer;

    ComputeModuleStatus status;

    class ComputeModuleWorkingEvent : public Event
    {
      private:
        ComputeModule *computeModule;
        bool loadToComputeQueueReadFlag;
        bool storeToComputeQueueReadFlag;
        bool computeToStoreQueueWriteFlag;
        bool computeToLoadQueueWriteFlag;

      public:
        ComputeModuleWorkingEvent(ComputeModule *computeModule);
        auto clearFlag() noexcept -> void;
        auto process() -> void override;
    };

    ComputeModuleWorkingEvent workingEvent;

    InstructionType instructionType;

    union Instruction
    {
        vta::Instruction::MemoryInstruction *memoryInstruction;
        vta::Instruction::GemmInstruction *gemmInstruction;
        vta::Instruction::AluInstruction *aluInstruction;
    };

    Instruction instruction;

  public:
    PARAMS(ComputeModule);

    ComputeModule(const Params &params);
};
} // namespace gem5

#endif
