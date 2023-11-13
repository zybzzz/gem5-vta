#include "vta/computer_module.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
ComputerModule::ComputerModule(const Params &params) :
    SimObject(params),
    CoreModule(params.computer_queue),
    cmp2StQueue(params.cmp2st_queue),
    st2CmpQueue(params.st2cmp_queue),
    cmp2LdQueue(params.cmp2ld_queue),
    ld2CmpQueue(params.ld2cmp_queue),
    inputBuffer(params.input_buffer),
    weightBuffer(params.weight_buffer),
    outputBuffer(params.output_buffer)
{
    DPRINTF(BaseVTAFlag, "create ComputerModule!\n");
}
} // namespace gem5
