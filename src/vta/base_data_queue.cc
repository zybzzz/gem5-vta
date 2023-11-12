#include "vta/base_data_queue.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
    BaseDataQueue::BaseDataQueue(const Params &params):
            SimObject(params){
        DPRINTF(BaseVTAFlag, "create BaseDataQueue!\n");
    }

    int BaseDataQueue::pushBack(){
        return 0;
    }

    int BaseDataQueue::popFront(){
        return 0;
    }


}