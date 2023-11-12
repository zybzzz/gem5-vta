#ifndef BUFFERS_HH
#define BUFFERS_HH

#include "vta/base_buffer.hh"
#include "params/InputBuffer.hh"
#include "params/WeightBuffer.hh"
#include "params/OutputBuffer.hh"
#include "sim/sim_object.hh"

namespace gem5
{
    class InputBuffer : public BaseBuffer{
        private:
        public:
            PARAMS(InputBuffer);
            InputBuffer(const Params &params);
    };

    class WeightBuffer : public BaseBuffer{
        private:
        public:
            PARAMS(WeightBuffer);
            WeightBuffer(const Params &params);
    };

    class OutputBuffer : public BaseBuffer{
        private:
        public:
            PARAMS(OutputBuffer);
            OutputBuffer(const Params &params);
    };
}

#endif