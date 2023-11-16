#ifndef COMPUTE_MODULE_HH
#define COMPUTE_MODULE_HH

#include "params/ComputeModule.hh"
#include "sim/sim_object.hh"
#include "vta/buffer.hh"
#include "vta/data_queue.hh"
#include "vta/instruction_queue.hh"

namespace gem5
{
class ComputeModule : public SimObject
{
  private:
    InstructionQueue *computeCommandQueue;

    DataQueue *computeToStoreQueue;
    DataQueue *storeToComputeQueue;
    DataQueue *computeToLoadQueue;
    DataQueue *loadToComputeQueue;

    Buffer *inputBuffer;
    Buffer *weightBuffer;
    Buffer *outputBuffer;

  public:
    PARAMS(ComputeModule);

    ComputeModule(const Params &params);
};
} // namespace gem5

#endif
