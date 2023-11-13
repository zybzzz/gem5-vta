#include "vta/compute_module.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
ComputeModule::ComputeModule(const Params &params) :
    SimObject(params),
    CoreModule(params.compute_queue),
    cmp2StQueue(params.cmp2st_queue),
    st2CmpQueue(params.st2cmp_queue),
    cmp2LdQueue(params.cmp2ld_queue),
    ld2CmpQueue(params.ld2cmp_queue),
    inputBuffer(params.input_buffer),
    weightBuffer(params.weight_buffer),
    outputBuffer(params.output_buffer)
{
    DPRINTF(BaseVTAFlag, "create ComputeModule!\n");
}
} // namespace gem5
