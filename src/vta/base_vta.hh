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
#include "vta/compute_module.hh"
#include "vta/instruction_fetch_module.hh"
#include "vta/load_module.hh"
#include "vta/store_module.hh"

using namespace std::literals;

namespace gem5
{

class BaseVTA : public SimObject
{
  private:
    InstructionFetchModule &instructionFetchModule;
    LoadModule &loadModule;
    ComputeModule &computeModule;
    StoreModule &storeModule;

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
        instructionFetchModule{*params.instruction_fetch_module},
        loadModule{*params.load_module},
        computeModule{*params.compute_module},
        storeModule{*params.store_module}
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
        loadModule.requestorId() =
            params().system->getRequestorId(&loadModule, "load_module");
        computeModule.requestorId() =
            params().system->getRequestorId(&computeModule, "compute_module");
        storeModule.requestorId() =
            params().system->getRequestorId(&storeModule, "store_module");

        instructionFetchModule.finishEvent() = &finishEvent;
        loadModule.finishEvent() = &finishEvent;
        computeModule.finishEvent() = &finishEvent;
        storeModule.finishEvent() = &finishEvent;
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
        if (if_name == "load_data_port"sv) {
            return loadModule.getPort(if_name, idx);
        }
        if (if_name == "micro_op_port"sv || if_name == "compute_data_port"sv) {
            return computeModule.getPort(if_name, idx);
        }
        if (if_name == "store_data_port"sv) {
            return storeModule.getPort(if_name, idx);
        }
        return SimObject::getPort(if_name, idx);
    }

    constexpr auto
    finish() -> bool
    {
        return instructionFetchModule.finish() && loadModule.finish() &&
               computeModule.finish() && storeModule.finish();
    }
};

} // namespace gem5

#endif
