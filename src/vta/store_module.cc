#include "vta/store_module.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
StoreModule::StoreModule(const Params &params) :
    SimObject(params),
    storeCommandQueue(params.store_command_queue),
    cmp2StQueue(params.cmp2st_queue),
    st2CmpQueue(params.st2cmp_queue),
    outputBuffer(params.output_buffer)
{
    DPRINTF(BaseVTAFlag, "create StoreModule!\n");
}
} // namespace gem5
