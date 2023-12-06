#include "vta/load_module.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
LoadModule::LoadModule(BaseVTA *vta) : vta(vta)
{
    DPRINTF(BaseVTAFlag, "create LoadModule!\n");
}
} // namespace gem5
