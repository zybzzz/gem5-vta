#include "vta/compute_module.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
ComputeModule::ComputeModule(BaseVTA *vta) : vta(vta)
{
    DPRINTF(BaseVTAFlag, "create ComputeModule!\n");
}
} // namespace gem5
