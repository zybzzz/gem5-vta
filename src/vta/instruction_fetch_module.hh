#ifndef INSTRUCTION_FETCH_MODULE_HH
#define INSTRUCTION_FETCH_MODULE_HH

#include "vta/vta_forward_declaration.hh"

namespace gem5
{
class InstructionFetchModule
{
  private:
    friend class BaseVTA;
    InstructionQueue *loadCommandQueue;
    InstructionQueue *computeCommandQueue;
    InstructionQueue *storeCommandQueue;

  public:
    InstructionFetchModule();
};
} // namespace gem5

#endif
