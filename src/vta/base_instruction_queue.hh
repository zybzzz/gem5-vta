#ifndef BASE_INSTRUCTION_QUEUE_HH
#define BASE_INSTRUCTION_QUEUE_HH

#include "params/BaseInstructionQueue.hh"
#include "sim/sim_object.hh"

namespace gem5
{
    class BaseInstructionQueue : public SimObject{
        private:
        public:
            PARAMS(BaseInstructionQueue);
            BaseInstructionQueue(const Params &params);
            virtual int pushBack();
            virtual int popFront();
    };
}

#endif