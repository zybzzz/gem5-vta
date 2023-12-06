#include "vta/instruction_fetch_module.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
InstructionFetchModule::InstructionFetchModule(BaseVTA *vta) : vta(vta)
{
    DPRINTF(BaseVTAFlag, "create InstructionFetchModule!\n");
}
} // namespace gem5
