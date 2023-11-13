#include "vta/instruction_fetch_module.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
InstructionFetchModule::InstructionFetchModule(const Params &params) :
    SimObject(params),
    loadCommandQueue(params.load_command_queue),
    computeCommandQueue(params.compute_command_queue),
    storeCommandQueue(params.store_command_queue)
{
    DPRINTF(BaseVTAFlag, "create InstructionFetchModule!\n");
}
} // namespace gem5
