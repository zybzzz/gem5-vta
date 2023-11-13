#include "vta/core_module.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
CoreModule::CoreModule(BaseInstructionQueue *baseInstructionQueue) :
    baseInstructionQueue(baseInstructionQueue)
{
    DPRINTF(BaseVTAFlag, "create baseInstructionQueue!\n");
}
} // namespace gem5
