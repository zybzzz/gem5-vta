#ifndef QUEUE_TIMING_PROTOCOL_HH
#define QUEUE_TIMING_PROTOCOL_HH

// this file is the simple version of protocol/timing.hh
namespace vta
{
template <typename T>
class QueueTimingPopProtocol;

template <typename T>
class QueueTimingPushProtocol
{
  private:
    friend class QueueTimingPopProtocol<T>;

  protected:
    virtual bool pushQueue() = 0;
};

template <typename T>
class QueueTimingPopProtocol
{
  private:
    friend class QueueTimingPushProtocol<T>;

  protected:
    virtual bool popQueue() = 0;
};
} // namespace vta

#endif
