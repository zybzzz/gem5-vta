#ifndef INST_QUEUES_HH
#define INST_QUEUES_HH

#include "vta/base_instruction_queue.hh"
#include "params/LoadQueue.hh"
#include "params/ComputerQueue.hh"
#include "params/StoreQueue.hh"


namespace gem5
{
    class LoadQueue : public BaseInstructionQueue{
        private:
        public:
            PARAMS(LoadQueue);
            LoadQueue(const Params &params);
    };

    class ComputerQueue : public BaseInstructionQueue{
        private:
        public:
            PARAMS(ComputerQueue);
            ComputerQueue(const Params &params);
    };

    class StoreQueue : public BaseInstructionQueue{
        private:
        public:
            PARAMS(StoreQueue);
            StoreQueue(const Params &params);
    };
}

#endif