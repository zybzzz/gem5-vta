#ifndef BASE_DATA_QUEUE_HH
#define BASE_DATA_QUEUE_HH

#include "params/BaseDataQueue.hh"
#include "sim/sim_object.hh"

namespace gem5
{
class BaseDataQueue : public SimObject
{
  private:
  public:
    PARAMS(BaseDataQueue);
    BaseDataQueue(const Params &params);
    virtual int pushBack();
    virtual int popFront();
};
} // namespace gem5

#endif
