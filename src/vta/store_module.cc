#include "vta/store_module.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
StoreModule::StoreModuleWorkingEvent::StoreModuleWorkingEvent(
    gem5::StoreModule *storeModule) :
    storeModule(storeModule)
{}

auto
StoreModule::StoreModuleWorkingEvent::process() -> void
{
    //    while (
    //        storeModule->instruction ||
    //        !storeModule->storeCommandQueue->empty()) { switch
    //        (storeModule->status) { case StoreModuleStatus::WaitToRead:
    //            if (storeModule->instruction == nullptr) {
    //                // get instruction from queue
    //            }
    //            if (storeModule->instruction->pop_next_dependence) {
    //                if (storeModule->computeToStoreQueue->tryPop()) {
    //                    storeModule->status = StoreModuleStatus::Normal;
    //                } else {
    //                    storeModule->reschedule(this, curTick() + 1);
    //                    return;
    //                }
    //            }
    //
    //            break;
    //        case StoreModuleStatus::Normal:
    //            // do memcpy then change to WaitToWrite
    //            break;
    //        case StoreModuleStatus::WaitToWrite:
    //            if (storeModule->instruction->push_next_dependence)
    //                if (storeModule->storeToComputeQueue->tryPush()) {
    //                    storeModule->status = StoreModuleStatus::WaitToRead;
    //                    // free instruction
    //                } else {
    //                    storeModule->status = StoreModuleStatus::WaitToWrite;
    //                    storeModule->reschedule(this, curTick() + 1);
    //                }
    //            break;
    //        }
    //    }
}

StoreModule::StoreModule(const Params &params) :
    SimObject(params),
    storeCommandQueue(params.store_command_queue),
    computeToStoreQueue(params.compute_to_store_queue),
    storeToComputeQueue(params.store_to_compute_queue),
    outputBuffer(params.output_buffer),
    status(StoreModuleStatus::Normal),
    workingEvent(this)

{
    DPRINTF(BaseVTAFlag, "create StoreModule!\n");
}

} // namespace gem5
