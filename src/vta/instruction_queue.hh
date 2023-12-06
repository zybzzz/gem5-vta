#ifndef INSTRUCTION_QUEUE_HH
#define INSTRUCTION_QUEUE_HH

#include "base/circular_queue.hh"
#include "base/types.hh"
#include "vta/communciation/queue_port.hh"
#include "vta/vta.hh"
#include "vta/vta_forward_declaration.hh"

namespace gem5
{
class InstructionQueue
{
  private:
    friend class BaseVTA;
    BaseVTA *vta;

    using Instruction = vta::Instruction;
    CircularQueue<Instruction *> queue;
    Tick readLatency;
    Tick writeLatency;

    class PushSidePort : public vta::QueuePushPort<Instruction *>
    {};

    PushSidePort pushSidePort;

  public:
    InstructionQueue(BaseVTA *vta);
    InstructionQueue(BaseVTA *vta, Tick readLatency, Tick writeLatency);

    size_t
    size() const
    {
        return queue.size();
    }
    void
    flush()
    {
        queue.flush();
    }
    bool
    canReadFromQueue() const
    {
        return !queue.empty();
    }
    bool
    canWriteToQueue() const
    {
        return !queue.full();
    }
    void
    pushBack(Instruction *instruction)
    {
        queue.push_back(instruction);
    }
    void
    popFront(Instruction *&instruction)
    {
        instruction = queue.front();
        queue.pop_front();
    }

    /**
     * Try to read data from the queue. If the read is successful, the queue
     * read latency will be returned. If the read fails, 0 will be
     * returned.
     * @param instruction This is a reference to a instruction pointer.
     * @return Return latency or 0.
     */
    Tick
    tryReadFromQueue(Instruction *&instruction)
    {
        if (canReadFromQueue()) {
            popFront(instruction);
            return readLatency;
        } else {
            return 0;
        }
    }

    /**
     * Try to write data to the queue. If the write is successful, return the
     * write latency. If this fails, 0 is returned.
     * @param instruction This is a pointer to a instruction.
     * @return Return latency or 0.
     */
    Tick
    tryWriteToQueue(Instruction *instruction)
    {
        if (canWriteToQueue()) {
            pushBack(instruction);
            return writeLatency;
        } else {
            return 0;
        }
    }
};
} // namespace gem5

#endif
