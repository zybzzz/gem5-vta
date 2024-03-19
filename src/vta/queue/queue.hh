#ifndef QUEUE_HH_
#define QUEUE_HH_

#include <cstddef>

#include "base/logging.hh"
#include "sim/cur_tick.hh"
#include "sim/eventq.hh"
#include "sim/sim_object.hh"
#include "vta/stream.hh"

namespace gem5
{

template <typename T, size_t N, size_t READ_DELAY, size_t WRITE_DELAY>
class Queue : public SimObject
{
    vta::Stream<T, N> data;
    enum class State
    {
        NORMAL,
        READ,
        WRITE,
    } state{};

  public:
    Queue(const Params &params) : SimObject{params} {}

    T read_buf;
    T write_buf;

    Event *producerEvent;
    Event *consumerEvent;

    auto
    read() noexcept -> void
    {
        switch (state) {
        case State::NORMAL:
            if (data.empty()) {
                state = State::READ;
            } else {
                read_buf = data.pop();
                schedule(consumerEvent, curTick() + READ_DELAY);
            }
            break;
        case State::READ:
            panic("Cannot pop while popping\n");
        case State::WRITE:
            read_buf = data.pop();
            schedule(consumerEvent, curTick() + READ_DELAY);
            data.push(write_buf);
            schedule(producerEvent, curTick() + READ_DELAY + WRITE_DELAY);
            state = State::NORMAL;
            break;
        }
    }

    auto
    write(const T &value) noexcept -> void
    {
        switch (state) {
        case State::NORMAL:
            if (data.full()) {
                write_buf = value;
                state = State::WRITE;
            } else {
                data.push(value);
                schedule(producerEvent, curTick() + READ_DELAY);
            }
            break;
        case State::READ:
            read_buf = value;
            schedule(producerEvent, curTick() + WRITE_DELAY);
            schedule(consumerEvent, curTick() + WRITE_DELAY + READ_DELAY);
            state = State::NORMAL;
            break;
        case State::WRITE:
            panic("Cannot push while pushing\n");
        }
    }
};

} // namespace gem5

#endif
