#ifndef DATA_QUEUES_HH
#define DATA_QUEUES_HH

#include "vta/base_data_queue.hh"
#include "params/CMP2STQueue.hh"
#include "params/ST2CMPQueue.hh"
#include "params/CMP2LDQueue.hh"
#include "params/LD2CMPQueue.hh"

namespace gem5
{
class CMP2STQueue : public BaseDataQueue
{
  private:
  public:
    PARAMS(CMP2STQueue);
    CMP2STQueue(const Params &params);
};

class ST2CMPQueue : public BaseDataQueue
{
  private:
  public:
    PARAMS(ST2CMPQueue);
    ST2CMPQueue(const Params &params);
};

class CMP2LDQueue : public BaseDataQueue
{
  private:
  public:
    PARAMS(CMP2LDQueue);
    CMP2LDQueue(const Params &params);
};

class LD2CMPQueue : public BaseDataQueue
{
  private:
  public:
    PARAMS(LD2CMPQueue);
    LD2CMPQueue(const Params &params);
};

} // namespace gem5

#endif
