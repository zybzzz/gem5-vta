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
    while (
        storeModule->instruction || !storeModule->storeCommandQueue->empty()) {
        switch (storeModule->status) {
        case StoreModuleStatus::WaitToRead:
            if (storeModule->instruction == nullptr) {
                // get instruction from queue
            }
            if (/*insn.pop_prev_dep*/ true) {
                if (storeModule->computeToStoreQueue->tryPop()) {
                    storeModule->status = StoreModuleStatus::Normal;
                } else {
                    return;
                }
            }

            break;
        case StoreModuleStatus::Normal:
            // do memcpy
            break;
        case StoreModuleStatus::WaitToWrite:
            if (/*insn.push_prev_dep*/ true)
                if (storeModule->storeToComputeQueue->tryPush()) {
                    storeModule->status = StoreModuleStatus::WaitToRead;
                    // free instruction
                } else {
                    storeModule->status = StoreModuleStatus::WaitToWrite;
                }
            break;
        }
    }
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

auto
StoreModule::notifyRead() -> void
{
    if (status == StoreModuleStatus::WaitToRead) {
        status = StoreModuleStatus::Normal;
        // schedule
        reschedule(workingEvent, curTick());
    } else {
    }
}

auto
StoreModule::notifyWrite() -> void
{
    if (status == StoreModuleStatus::WaitToWrite) {
        status = StoreModuleStatus::Normal;
        // schedule
        reschedule(workingEvent, curTick());
    } else {
    }
}

} // namespace gem5
