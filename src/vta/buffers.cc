#include "vta/buffers.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
InputBuffer::InputBuffer(const Params &params) : BaseBuffer(params)
{
    DPRINTF(BaseVTAFlag, "create InputBuffer!\n");
}

WeightBuffer::WeightBuffer(const Params &params) : BaseBuffer(params)
{
    DPRINTF(BaseVTAFlag, "create WeightBuffer!\n");
}

OutputBuffer::OutputBuffer(const Params &params) : BaseBuffer(params)
{
    DPRINTF(BaseVTAFlag, "create OutputBuffer!\n");
}
} // namespace gem5
