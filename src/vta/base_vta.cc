#include "vta/base_vta.hh"

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"

namespace gem5
{
BaseVTA::BaseVTA(const Params &params) :
    SimObject(params),
    begin_event([this] { processBeginEvent(); }, name() + ".beginEvent")
{
    DPRINTF(BaseVTAFlag, "===========================================\n");
    DPRINTF(BaseVTAFlag, "initializing gem5-vta ... user configuration "
                         "parameters are as follows: \n");
    DPRINTF(BaseVTAFlag, "===========================================\n");
}

void
BaseVTA::startup()
{
    // DPRINTF(BaseVTAFlag, "%s: start up in BaseVTA.\n", __func__);
    // schedule(begin_event, 100);
}

void
BaseVTA::processBeginEvent()
{
    // DPRINTF(BaseVTAFlag, "%s: process event up in BaseVTA.\n", __func__);
}
} // namespace gem5
