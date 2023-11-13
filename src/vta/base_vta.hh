#ifndef BASE_VTA_HH
#define BASE_VTA_HH

#include "params/BaseVTA.hh"
#include "sim/sim_object.hh"
#include "string"

namespace gem5
{

class BaseVTA : public SimObject
{
  private:
    // VTA configs
    std::string hardware_version;
    int input_data_width;
    int weight_data_width;
    int accumulator_data_width;
    int batch_size;
    int block_size;
    int uop_buffer_size;
    int input_buffer_size;
    int weight_buffer_size;
    int accumulator_buffer_size;

    EventFunctionWrapper begin_event;
    void processBeginEvent();

  public:
    PARAMS(BaseVTA);
    BaseVTA(const Params &params);

    virtual void startup() override;
};

} // namespace gem5

#endif
