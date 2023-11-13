#ifndef CORE_MODULE_HH
#define CORE_MODULE_HH

#include "vta/base_instruction_queue.hh"

namespace gem5
{
class CoreModule
{
  private:
  protected:
    BaseInstructionQueue *baseInstructionQueue;
    CoreModule(BaseInstructionQueue *baseInstructionQueue);
};
} // namespace gem5
#endif
