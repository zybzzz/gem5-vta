#ifndef STORE_MODULE_HH
#define STORE_MODULE_HH

#include "vta/vta_forward_declaration.hh"

namespace gem5
{
class StoreModule
{
  private:
    friend class BaseVTA;
    InstructionQueue *storeCommandQueue;

    DataQueue *computeToStoreQueue;
    DataQueue *storeToComputeQueue;

    Buffer *outputBuffer;

  public:
    StoreModule();
};
} // namespace gem5

#endif
