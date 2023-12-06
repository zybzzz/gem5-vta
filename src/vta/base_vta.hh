#ifndef BASE_VTA_HH
#define BASE_VTA_HH

#include "params/BaseVTA.hh"
#include "sim/sim_object.hh"
#include "vta/buffer.hh"
#include "vta/compute_module.hh"
#include "vta/data_queue.hh"
#include "vta/instruction_fetch_module.hh"
#include "vta/instruction_queue.hh"
#include "vta/load_module.hh"
#include "vta/store_module.hh"

namespace gem5
{

class BaseVTA : public SimObject
{
  private:
    EventFunctionWrapper begin_event;

    void processBeginEvent();

  protected:
    // buffers
    Buffer inputBuffer;
    Buffer weightBuffer;
    Buffer outputBuffer;

    // data queues
    DataQueue computeToStoreQueue;
    DataQueue storeToComputeQueue;
    DataQueue computeToLoadQueue;
    DataQueue loadToComputeQueue;

    // command queues
    InstructionQueue loadQueue;
    InstructionQueue computeCommandQueue;
    InstructionQueue storeQueue;

    // regular module
    InstructionFetchModule instructionFetchModule;
    ComputeModule computeModule;
    LoadModule loadModule;
    StoreModule storeModule;

  public:
    PARAMS(BaseVTA);

    BaseVTA(const Params &params);

    virtual void startup() override;
};

} // namespace gem5

#endif
