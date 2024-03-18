#ifndef COMPUTE_MODULE_HH
#define COMPUTE_MODULE_HH

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"
#include "params/ComputeModule.hh"
#include "sim/sim_object.hh"
#include "vta/buffer.hh"
#include "vta/command_queue.hh"
#include "vta/dependency_queue.hh"

namespace gem5
{

class ComputeModule : public SimObject
{
  private:
    CommandQueue &computeCommandQueue;

    DependencyQueue &loadToComputeQueue;
    DependencyQueue &computeToLoadQueue;
    DependencyQueue &computeToStoreQueue;
    DependencyQueue &storeToComputeQueue;

    Buffer &inputBuffer;
    Buffer &weightBuffer;
    Buffer &outputBuffer;

  public:
    PARAMS(ComputeModule);

    ComputeModule(const Params &params) :
        SimObject{params},
        computeCommandQueue{*params.compute_command_queue},
        loadToComputeQueue{*params.load_to_compute_queue},
        computeToLoadQueue{*params.compute_to_load_queue},
        computeToStoreQueue{*params.compute_to_store_queue},
        storeToComputeQueue{*params.store_to_compute_queue},
        inputBuffer{*params.input_buffer},
        weightBuffer{*params.weight_buffer},
        outputBuffer{*params.output_buffer}
    {}
};

} // namespace gem5

#endif
