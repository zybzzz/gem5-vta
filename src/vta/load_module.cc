#include "vta/load_module.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
LoadModule::LoadModuleWorkingEvent::LoadModuleWorkingEvent(
    gem5::LoadModule *loadModule) :
    loadModule(loadModule)
{}

auto
LoadModule::LoadModuleWorkingEvent::process() -> void
{
    while (loadModule->instruction || !loadModule->loadCommandQueue->empty()) {
        switch (loadModule->status) {
        case LoadModuleStatus::WaitToRead:
            if (loadModule->instruction == nullptr) {
                // get instruction from queue
            }
            if (/*insn.pop_prev_dep*/ true) {
                if (loadModule->computeToLoadQueue->tryPop()) {
                    loadModule->status = LoadModuleStatus::Normal;
                } else {
                    loadModule->reschedule(this, curTick() + 1);
                    return;
                }
            }

            break;
        case LoadModuleStatus::Normal:
            // judge and do load
            break;
        case LoadModuleStatus::WaitToWrite:
            if (/*insn.push_prev_dep*/ true)
                if (loadModule->loadToComputeQueue->tryPush()) {
                    loadModule->status = LoadModuleStatus::WaitToRead;
                    // free instruction
                } else {
                    loadModule->status = LoadModuleStatus::WaitToWrite;
                    loadModule->reschedule(this, curTick() + 1);
                }
            break;
        }
    }
}

LoadModule::LoadModule(const Params &params) :
    SimObject(params),
    loadCommandQueue(params.load_command_queue),
    computeToLoadQueue(params.compute_to_load_queue),
    loadToComputeQueue(params.load_to_compute_queue),
    inputBuffer(params.input_buffer),
    weightBuffer(params.weight_buffer),
    status(LoadModuleStatus::WaitToRead),
    workingEvent(this),
    instruction(nullptr)
{
    DPRINTF(BaseVTAFlag, "create LoadModule!\n");
}
} // namespace gem5
