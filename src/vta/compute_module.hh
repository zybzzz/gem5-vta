#ifndef COMPUTE_MODULE_HH
#define COMPUTE_MODULE_HH

#include "vta/vta_forward_declaration.hh"

namespace gem5
{
class ComputeModule
{
  private:
    friend class BaseVTA;
    InstructionQueue *computeCommandQueue;

    DataQueue *computeToStoreQueue;
    DataQueue *storeToComputeQueue;
    DataQueue *computeToLoadQueue;
    DataQueue *loadToComputeQueue;

    Buffer *inputBuffer;
    Buffer *weightBuffer;
    Buffer *outputBuffer;

  public:
    ComputeModule();
};
} // namespace gem5

#endif
