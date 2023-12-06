#ifndef PORT_HH
#define PORT_HH

#include <cassert>
#include <ostream>
#include <string>

#include "base/types.hh"

// this file is the simple version of sim/port.hh
namespace vta
{
class Port
{
  private:
    /** Descriptive name (for DPRINTF output) */
    const std::string portName;

  protected:
    class UnboundPortException
    {};

    [[noreturn]] void reportUnbound() const;

    /**
     * A pointer to this port's peer.
     */
    Port *_peer;

    /**
     * Whether this port is currently connected to a peer port.
     */
    bool _connected;

    /**
     * Abstract base class for ports
     *
     * @param _name Port name including the owners name
     * @param _id A port identifier for vector ports
     */
    Port(const std::string &_name);

  public:
    /**
     * Virtual destructor due to inheritance.
     */
    virtual ~Port();

    /** Return a reference to this port's peer. */
    Port &
    getPeer()
    {
        return *_peer;
    }

    /** Return port name (for DPRINTF). */
    const std::string
    name() const
    {
        return portName;
    }

    /** Attach to a peer port. */
    virtual void
    bind(Port &peer)
    {
        _peer = &peer;
        _connected = true;
    }

    /** Dettach from a peer port. */
    virtual void
    unbind()
    {
        _peer = nullptr;
        _connected = false;
    }

    /** Is this port currently connected to a peer? */
    bool
    isConnected() const
    {
        return _connected;
    }

    /** A utility function to make it easier to swap out ports. */
    void
    takeOverFrom(Port *old)
    {
        assert(old);
        assert(old->isConnected());
        assert(!isConnected());
        Port &peer = old->getPeer();
        assert(peer.isConnected());

        // Disconnect the original binding.
        old->unbind();
        peer.unbind();

        // Connect the new binding.
        peer.bind(*this);
        bind(peer);
    }
};

static inline std::ostream &
operator<<(std::ostream &os, const Port &port)
{
    os << port.name();
    return os;
}

} // namespace vta

#endif
