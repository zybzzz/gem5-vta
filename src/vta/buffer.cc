#include "vta/buffer.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
Buffer::Buffer(BaseVTA *vta) : vta(vta)
{
    DPRINTF(BaseVTAFlag, "create Buffer!\n");
}
} // namespace gem5
