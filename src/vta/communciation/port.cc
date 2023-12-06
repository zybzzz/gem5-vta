#include "vta/communciation/port.hh"

#include "base/logging.hh"

namespace vta
{

Port::Port(const std::string &_name) :
    portName(_name), _peer(nullptr), _connected(false)
{}
Port::~Port() {}

void
Port::reportUnbound() const
{
    fatal("%s: Unconnected port!", name());
}

} // namespace vta
