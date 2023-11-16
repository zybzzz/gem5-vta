#ifndef STORE_MODULE_HH
#define STORE_MODULE_HH

#include "params/StoreModule.hh"
#include "sim/sim_object.hh"
#include "vta/buffer.hh"
#include "vta/instruction_queue.hh"

namespace gem5
{
class StoreModule : public SimObject
{
  private:
    InstructionQueue *storeCommandQueue;

    DataQueue *computeToStoreQueue;
    DataQueue *storeToComputeQueue;

    Buffer *outputBuffer;

  public:
    PARAMS(StoreModule);

    StoreModule(const Params &params);
};
} // namespace gem5

#endif
