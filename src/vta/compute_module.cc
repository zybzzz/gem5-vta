#include "vta/compute_module.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{

ComputeModule::ComputeModule(const Params &params) :
    SimObject(params),
    computeCommandQueue(params.compute_command_queue),
    computeToStoreQueue(params.compute_to_store_queue),
    storeToComputeQueue(params.store_to_compute_queue),
    computeToLoadQueue(params.compute_to_load_queue),
    loadToComputeQueue(params.load_to_compute_queue),
    inputBuffer(params.input_buffer),
    weightBuffer(params.weight_buffer),
    outputBuffer(params.output_buffer)
{
    DPRINTF(BaseVTAFlag, "create ComputeModule!\n");
}
} // namespace gem5
