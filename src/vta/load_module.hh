#ifndef LOAD_MODULE_HH
#define LOAD_MODULE_HH

#include "params/LoadModule.hh"
#include "sim/sim_object.hh"
#include "vta/buffer.hh"
#include "vta/instruction_queue.hh"

namespace gem5
{
class LoadModule : public SimObject
{
  private:
    InstructionQueue *loadCommandQueue;
    DataQueue *cmp2LdQueue;
    DataQueue *ld2CmpQueue;

    Buffer *inputBuffer;
    Buffer *weightBuffer;

  public:
    PARAMS(LoadModule);
    LoadModule(const Params &params);
};
} // namespace gem5

#endif
