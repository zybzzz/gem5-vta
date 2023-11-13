#ifndef INSTRUCTION_FETCH_MODULE_HH
#define INSTRUCTION_FETCH_MODULE_HH

#include "params/InstructionFetchModule.hh"
#include "sim/sim_object.hh"
#include "vta/base_instruction_queue.hh"

namespace gem5
{
class InstructionFetchModule : public SimObject
{
  private:
    BaseInstructionQueue *loadQueue;
    BaseInstructionQueue *computerQueue;
    BaseInstructionQueue *storeQueue;

  public:
    PARAMS(InstructionFetchModule);
    InstructionFetchModule(const Params &params);
};
} // namespace gem5

#endif
