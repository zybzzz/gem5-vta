#include "vta/buffer.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
Buffer::Buffer(const Params &params) : SimObject(params)
{
    DPRINTF(BaseVTAFlag, "create Buffer!\n");
}
} // namespace gem5
