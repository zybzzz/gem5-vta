#include "vta/load_module.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
LoadModule::LoadModule(const Params &params) :
    SimObject(params),
    loadCommandQueue(params.load_command_queue),
    computeToLoadQueue(params.compute_to_load_queue),
    loadToComputeQueue(params.load_to_compute_queue),
    inputBuffer(params.input_buffer),
    weightBuffer(params.weight_buffer)
{
    DPRINTF(BaseVTAFlag, "create LoadModule!\n");
}
} // namespace gem5
