#ifndef CORE_MODULE_HH
#define CORE_MODULE_HH

#include "vta/instruction_queue.hh"

namespace gem5
{
class CoreModule
{
  private:
  protected:
    InstructionQueue *baseInstructionQueue;
    CoreModule(InstructionQueue *baseInstructionQueue);
};
} // namespace gem5
#endif
