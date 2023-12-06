#ifndef LOAD_MODULE_HH
#define LOAD_MODULE_HH

#include "vta/vta_forward_declaration.hh"

namespace gem5
{
class LoadModule
{
  private:
    friend class BaseVTA;
    BaseVTA *vta;

    InstructionQueue *loadCommandQueue;

    DataQueue *computeToLoadQueue;
    DataQueue *loadToComputeQueue;

    Buffer *inputBuffer;
    Buffer *weightBuffer;

  public:
    LoadModule(BaseVTA *vta);
};
} // namespace gem5

#endif
