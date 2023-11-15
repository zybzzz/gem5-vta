#ifndef BASE_VTA_HH
#define BASE_VTA_HH

#include "params/BaseVTA.hh"
#include "sim/sim_object.hh"
#include "string"

namespace gem5
{

class BaseVTA : public SimObject
{
  private:
    EventFunctionWrapper begin_event;

    void processBeginEvent();

  public:
    PARAMS(BaseVTA);

    BaseVTA(const Params &params);

    virtual void startup() override;
};

} // namespace gem5

#endif
