#ifndef WEIGHT_BUFFER_HH
#define WEIGHT_BUFFER_HH

#include "params/WeightBuffer.hh"
#include "sim/sim_object.hh"
#include "vta/buffer/buffer.hh"
#include "vta/vta.hh"

namespace gem5
{

class WeightBuffer :
    public SimObject,
    public Buffer<vta::Bus, vta::WEIGHT_BUFFER_DEPTH, vta::WEIGHT_MATRIX_RATIO,
        1, 1>
{
  public:
    PARAMS(WeightBuffer);

    WeightBuffer(const Params &params) : SimObject{params} {};
};

} // namespace gem5

#endif
