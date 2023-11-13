#ifndef COMPUTE_MODULE_HH
#define COMPUTE_MODULE_HH

#include "params/ComputeModule.hh"
#include "sim/sim_object.hh"
#include "vta/buffer.hh"
#include "vta/core_module.hh"
#include "vta/data_queue.hh"

namespace gem5
{
class ComputeModule : public SimObject, CoreModule
{
  private:
    DataQueue *cmp2StQueue;
    DataQueue *st2CmpQueue;
    DataQueue *cmp2LdQueue;
    DataQueue *ld2CmpQueue;

    Buffer *inputBuffer;
    Buffer *weightBuffer;
    Buffer *outputBuffer;

  public:
    PARAMS(ComputeModule);
    ComputeModule(const Params &params);
};
} // namespace gem5

#endif
