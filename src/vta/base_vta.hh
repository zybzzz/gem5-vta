#ifndef BASE_VTA_HH
#define BASE_VTA_HH

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"
#include "params/BaseVTA.hh"
#include "sim/sim_object.hh"
#include "vta/vta.hh"

namespace gem5
{

class BaseVTA : public SimObject
{
  private:
    vta::CommandQueue loadCommandQueue{};
    vta::CommandQueue computeCommandQueue{};
    vta::CommandQueue storeCommandQueue{};

  public:
    PARAMS(BaseVTA);

    BaseVTA(const Params &params) : SimObject(params)
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
