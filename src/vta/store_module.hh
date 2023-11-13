#ifndef STORE_MODULE_HH
#define STORE_MODULE_HH

#include "vta/core_module.hh"
#include "vta/buffers.hh"
#include "params/StoreModule.hh"
#include "sim/sim_object.hh"

namespace gem5
{
class StoreModule : public SimObject, public CoreModule
{
  private:
    CMP2STQueue *cmp2StQueue;
    ST2CMPQueue *st2CmpQueue;

    OutputBuffer *outputBuffer;

  public:
    PARAMS(StoreModule);
    StoreModule(const Params &params);
};
} // namespace gem5

#endif
