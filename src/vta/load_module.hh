#ifndef LOAD_MODULE_HH
#define LOAD_MODULE_HH

#include "params/LoadModule.hh"
#include "sim/sim_object.hh"
#include "vta/buffer.hh"
#include "vta/core_module.hh"

namespace gem5
{
class LoadModule : public SimObject, public CoreModule
{
  private:
    DataQueue *cmp2LdQueue;
    DataQueue *ld2CmpQueue;

    Buffer *inputBuffer;
    Buffer *weightBuffer;

  public:
    PARAMS(LoadModule);
    LoadModule(const Params &params);
};
} // namespace gem5

#endif
