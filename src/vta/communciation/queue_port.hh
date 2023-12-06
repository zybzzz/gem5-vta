#ifndef QUEUE_PORT_HH
#define QUEUE_PORT_HH

#include "vta/communciation/port.hh"
#include "vta/communciation/queue_timing_protocol.hh"

namespace vta
{

class BaseVTA;

template <typename T>
class QueuePopPort;

template <typename T>
class QueuePushPort : public Port, public QueueTimingPushProtocol<T>
{
  private:
    friend QueuePopPort<T>;
    BaseVTA *vta;

  protected:
    virtual bool pushQueue() override;

  public:
    bool pushToQueue();
};

template <typename T>
class QueuePopPort : public Port, public QueueTimingPopProtocol<T>
{
  private:
    friend QueuePushPort<T>;
    BaseVTA *vta;

  protected:
    virtual bool popQueue() override;

  public:
    bool popFromQueue();
};

} // namespace vta

#endif
