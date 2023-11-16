#include "vta/store_module.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
StoreModule::StoreModule(const Params &params) :
    SimObject(params),
    storeCommandQueue(params.store_command_queue),
    computeToStoreQueue(params.compute_to_store_queue),
    storeToComputeQueue(params.store_to_compute_queue),
    outputBuffer(params.output_buffer)
{
    DPRINTF(BaseVTAFlag, "create StoreModule!\n");
}
} // namespace gem5
