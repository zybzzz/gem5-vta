#ifndef LOAD_MODULE_HH
#define LOAD_MODULE_HH

#include "vta/core_module.hh"
#include "vta/buffers.hh"
#include "params/LoadModule.hh"
#include "sim/sim_object.hh"

namespace gem5
{
    class LoadModule : public SimObject, public CoreModule{
        private:
            CMP2LDQueue *cmp2LdQueue;
            LD2CMPQueue *ld2CmpQueue;

            InputBuffer *inputBuffer;
            WeightBuffer *weightBuffer;
        public:
            PARAMS(LoadModule);
            LoadModule(const Params &params);
    };
}

#endif