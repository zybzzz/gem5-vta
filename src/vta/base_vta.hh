#ifndef BASE_VTA_HH
#define BASE_VTA_HH

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"
#include "params/BaseVTA.hh"
#include "sim/sim_object.hh"
#include "vta/instruction_fetch_module.hh"

namespace gem5
{

class BaseVTA : public SimObject
{
  private:
    InstructionFetchModule &instructionFetchModule;

  public:
    PARAMS(BaseVTA);

    BaseVTA(const Params &params) :
        SimObject{params},
        instructionFetchModule{*params.instruction_fetch_module}
    {
        DPRINTF(BaseVTAFlag, "===========================================\n");
        DPRINTF(BaseVTAFlag, "initializing gem5-vta ... user configuration "
                             "parameters are as follows: \n");
        DPRINTF(BaseVTAFlag, "===========================================\n");
    }

    virtual void
    startup() override
    {}
};

} // namespace gem5

#endif
