#include "vta/instruction_fetch_module.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
InstructionFetchModule::InstructionFetchModule(const Params &params) :
    SimObject(params),
    loadQueue(params.load_queue),
    computeQueue(params.compute_queue),
    storeQueue(params.store_queue)
{
    DPRINTF(BaseVTAFlag, "create InstructionFetchModule!\n");
}
} // namespace gem5
