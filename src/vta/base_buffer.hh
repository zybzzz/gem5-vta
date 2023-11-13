#ifndef BASE_BUFFER_HH
#define BASE_BUFFER_HH

#include "params/BaseBuffer.hh"
#include "sim/sim_object.hh"

namespace gem5
{
class BaseBuffer : public SimObject
{
  private:
  public:
    PARAMS(BaseBuffer);
    BaseBuffer(const Params &params);
};
} // namespace gem5

#endif
