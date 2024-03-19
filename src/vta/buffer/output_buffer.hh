#ifndef OUTPUT_BUFFER_HH
#define OUTPUT_BUFFER_HH

#include "params/OutputBuffer.hh"
#include "sim/sim_object.hh"
#include "vta/buffer/buffer.hh"
#include "vta/vta.hh"

namespace gem5
{

class OutputBuffer :
    public SimObject,
    public Buffer<vta::Bus, vta::OUTPUT_BUFFER_DEPTH, vta::OUTPUT_MATRIX_RATIO,
        1, 1>
{
  public:
    PARAMS(OutputBuffer);

    OutputBuffer(const Params &params) : SimObject{params} {};
};

} // namespace gem5

#endif
