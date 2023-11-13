#ifndef DATA_QUEUE_HH
#define DATA_QUEUE_HH

#include "params/DataQueue.hh"
#include "sim/sim_object.hh"

namespace gem5
{
class DataQueue : public SimObject
{
  private:
  public:
    PARAMS(DataQueue);
    DataQueue(const Params &params);
    virtual int pushBack();
    virtual int popFront();
};
} // namespace gem5

#endif
