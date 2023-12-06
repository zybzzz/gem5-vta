#include "vta/store_module.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
StoreModule::StoreModule(BaseVTA *vta) : vta(vta)
{
    DPRINTF(BaseVTAFlag, "create StoreModule!\n");
}
} // namespace gem5
