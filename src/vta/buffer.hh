#ifndef BUFFER_HH
#define BUFFER_HH

#include "params/Buffer.hh"
#include "sim/sim_object.hh"

namespace gem5
{

class Buffer : public SimObject
{
  public:
    PARAMS(Buffer);

    Buffer(const Params &params) : SimObject{params} {};
};

} // namespace gem5

#endif
