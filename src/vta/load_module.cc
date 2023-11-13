#include "vta/load_module.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
LoadModule::LoadModule(const Params &params) :
    SimObject(params),
    loadCommandQueue(params.load_command_queue),
    cmp2LdQueue(params.cmp2ld_queue),
    ld2CmpQueue(params.ld2cmp_queue),
    inputBuffer(params.input_buffer),
    weightBuffer(params.weight_buffer)
{
    DPRINTF(BaseVTAFlag, "create LoadModule!\n");
}
} // namespace gem5
