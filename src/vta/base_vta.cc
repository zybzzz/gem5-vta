#include "vta/base_vta.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"
#include "vta/buffer.hh"
#include "vta/compute_module.hh"
#include "vta/data_queue.hh"
#include "vta/instruction_fetch_module.hh"
#include "vta/instruction_queue.hh"
#include "vta/load_module.hh"
#include "vta/store_module.hh"

namespace gem5
{
BaseVTA::BaseVTA(const Params &params) :
    SimObject(params),
    begin_event([this] { processBeginEvent(); }, name() + ".beginEvent"),
    inputBuffer(new Buffer(this)),
    weightBuffer(new Buffer(this)),
    outputBuffer(new Buffer(this)),
    computeToStoreQueue(new DataQueue(this)),
    storeToComputeQueue(new DataQueue(this)),
    computeToLoadQueue(new DataQueue(this)),
    loadToComputeQueue(new DataQueue(this)),
    loadQueue(new InstructionQueue(this)),
    computeCommandQueue(new InstructionQueue(this)),
    storeQueue(new InstructionQueue(this)),
    instructionFetchModule(new InstructionFetchModule(this)),
    computeModule(new ComputeModule(this)),
    loadModule(new LoadModule(this)),
    storeModule(new StoreModule(this))
{
    DPRINTF(BaseVTAFlag, "===========================================\n");
    DPRINTF(BaseVTAFlag, "initializing gem5-vta ... user configuration "
                         "parameters are as follows: \n");
    DPRINTF(BaseVTAFlag, "===========================================\n");

    // connection
    // instruction fetch module
    instructionFetchModule->loadCommandQueue = loadQueue;
    instructionFetchModule->computeCommandQueue = computeCommandQueue;
    instructionFetchModule->storeCommandQueue = storeQueue;

    // computer module
    computeModule->computeCommandQueue = computeCommandQueue;
    computeModule->loadToComputeQueue = loadToComputeQueue;
    computeModule->computeToLoadQueue = computeToLoadQueue;
    computeModule->storeToComputeQueue = storeToComputeQueue;
    computeModule->computeToStoreQueue = computeToStoreQueue;
    computeModule->inputBuffer = inputBuffer;
    computeModule->weightBuffer = weightBuffer;
    computeModule->outputBuffer = outputBuffer;

    // load module
    loadModule->loadCommandQueue = loadQueue;
    loadModule->computeToLoadQueue = computeToLoadQueue;
    loadModule->loadToComputeQueue = loadToComputeQueue;
    loadModule->inputBuffer = inputBuffer;
    loadModule->weightBuffer = weightBuffer;

    // store module
    storeModule->storeCommandQueue = storeQueue;
    storeModule->computeToStoreQueue = computeToStoreQueue;
    storeModule->storeToComputeQueue = storeToComputeQueue;
    storeModule->outputBuffer = outputBuffer;
}

void
BaseVTA::startup()
{
    // DPRINTF(BaseVTAFlag, "%s: start up in BaseVTA.\n", __func__);
    // schedule(begin_event, 100);
}

void
BaseVTA::processBeginEvent()
{
    // DPRINTF(BaseVTAFlag, "%s: process event up in BaseVTA.\n", __func__);
}
} // namespace gem5
