#ifndef INSTRUCTION_QUEUE_HH
#define INSTRUCTION_QUEUE_HH

#include "base/circular_queue.hh"
#include "params/InstructionQueue.hh"
#include "sim/clocked_object.hh"
#include "vta/base/vta_instruction.hh"

namespace gem5
{
class InstructionQueue : public ClockedObject
{
  private:
    CircularQueue<VTAInstruction *> queue;
    Tick readLatency;
    Tick writeLatency;

  public:
    PARAMS(InstructionQueue);

    InstructionQueue(const Params &params);

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
    pushBack(VTAInstruction *instruction)
    {
        queue.push_back(instruction);
    }
    void
    popFront(VTAInstruction *&instruction)
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
    tryReadFromQueue(VTAInstruction *&instruction)
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
    tryWriteToQueue(VTAInstruction *instruction)
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
