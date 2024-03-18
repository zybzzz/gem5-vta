#ifndef BASE_VTA_HH
#define BASE_VTA_HH

#include <string>
#include <string_view>

#include "base/trace.hh"
#include "debug/BaseVTAFlag.hh"
#include "params/BaseVTA.hh"
#include "sim/eventq.hh"
#include "sim/sim_events.hh"
#include "sim/sim_object.hh"
#include "sim/system.hh"
#include "vta/instruction_fetch_module.hh"

using namespace std::literals;

namespace gem5
{

class BaseVTA : public SimObject
{
  private:
    InstructionFetchModule &instructionFetchModule;

    class FinishEvent : public Event
    {
      private:
        BaseVTA &owner;

      public:
        FinishEvent(BaseVTA &owner) : owner{owner} {}

        virtual auto
        process() -> void override
        {
            if (owner.finish()) {
                new GlobalSimLoopExitEvent{"Finish simulation\n", 0, 0};
            }
        }
    } finishEvent{*this};

  public:
    PARAMS(BaseVTA);

    BaseVTA(const Params &params) :
        SimObject{params},
        instructionFetchModule{*params.instruction_fetch_module}
    {
        DPRINTF(BaseVTAFlag, "===========================================\n");
        DPRINTF(BaseVTAFlag, "initializing gem5-vta ... user configuration "
                             "parameters are as follows: \n");
        DPRINTF(BaseVTAFlag, "===========================================\n");
    }

    virtual void
    init() override
    {
        instructionFetchModule.requestorId() = params().system->getRequestorId(
            &instructionFetchModule, "instruction_fetch_module");
        instructionFetchModule.finishEvent() = &finishEvent;
    }

    virtual void
    startup() override
    {}

    virtual auto
    getPort(const std::string &if_name,
        PortID idx = InvalidPortID) -> Port & override
    {
        if (if_name == "instruction_port"sv) {
            return instructionFetchModule.getPort(if_name, idx);
        }
        return SimObject::getPort(if_name, idx);
    }

    constexpr auto
    finish() -> bool
    {
        return instructionFetchModule.finish();
    }
};

} // namespace gem5

#endif
