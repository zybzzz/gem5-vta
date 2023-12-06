#ifndef DATA_QUEUE_HH
#define DATA_QUEUE_HH

#include "vta/vta_forward_declaration.hh"

namespace gem5
{
class DataQueue
{
  private:
    friend class BaseVTA;

  public:
    DataQueue();

    int pushBack();

    int popFront();
};
} // namespace gem5

#endif
