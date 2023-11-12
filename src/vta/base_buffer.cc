#include "vta/base_buffer.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
    BaseBuffer::BaseBuffer(const Params &params):
            SimObject(params){
        DPRINTF(BaseVTAFlag, "create BaseBuffer!\n");
    }
}