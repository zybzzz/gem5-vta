#include "vta/instruction_fetch_module.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
InstructionFetchModule::InstructionFetchModule(const Params &params) :
    SimObject(params),
    loadQueue(params.load_queue),
    computerQueue(params.computer_queue),
    storeQueue(params.store_queue)
{
    DPRINTF(BaseVTAFlag, "create InstructionFetchModule!\n");
}
} // namespace gem5
