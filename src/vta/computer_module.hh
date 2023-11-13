#ifndef COMPUTER_MODULE_HH
#define COMPUTER_MODULE_HH

#include "vta/core_module.hh"
#include "vta/data_queues.hh"
#include "vta/buffers.hh"
#include "params/ComputerModule.hh"
#include "sim/sim_object.hh"

namespace gem5
{
class ComputerModule : public SimObject, CoreModule
{
  private:
    CMP2STQueue *cmp2StQueue;
    ST2CMPQueue *st2CmpQueue;
    CMP2LDQueue *cmp2LdQueue;
    LD2CMPQueue *ld2CmpQueue;

    InputBuffer *inputBuffer;
    WeightBuffer *weightBuffer;
    OutputBuffer *outputBuffer;

  public:
    PARAMS(ComputerModule);
    ComputerModule(const Params &params);
};
} // namespace gem5

#endif
