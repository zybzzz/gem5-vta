#ifndef INPUT_BUFFER_HH
#define INPUT_BUFFER_HH

#include "params/InputBuffer.hh"
#include "sim/sim_object.hh"
#include "vta/buffer/buffer.hh"
#include "vta/vta.hh"

namespace gem5
{

class InputBuffer :
    public SimObject,
    public Buffer<vta::Bus, vta::INPUT_BUFFER_DEPTH, vta::INPUT_MATRIX_RATIO,
        1, 1>
{
  public:
    PARAMS(InputBuffer);

    InputBuffer(const Params &params) : SimObject{params} {};
};

} // namespace gem5

#endif
