#include "vta/data_queues.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
    CMP2STQueue::CMP2STQueue(const Params &params):
            BaseDataQueue(params){
        DPRINTF(BaseVTAFlag, "create CMP2STQueue!\n");
    }
}

namespace gem5
{
    ST2CMPQueue::ST2CMPQueue(const Params &params):
            BaseDataQueue(params){
        DPRINTF(BaseVTAFlag, "create ST2CMPQueue!\n");
    }
}

namespace gem5
{
    CMP2LDQueue::CMP2LDQueue(const Params &params):
            BaseDataQueue(params){
        DPRINTF(BaseVTAFlag, "create CMP2LDQueue!\n");
    }
}

namespace gem5
{
    LD2CMPQueue::LD2CMPQueue(const Params &params):
            BaseDataQueue(params){
        DPRINTF(BaseVTAFlag, "create LD2CMPQueue!\n");
    }
}