#ifndef BUFFER_HH
#define BUFFER_HH

#include "vta/vta_forward_declaration.hh"

namespace gem5
{
class Buffer
{
  private:
    friend class BaseVTA;
    BaseVTA *vta;

  public:
    Buffer(BaseVTA *vta);
};
} // namespace gem5

#endif
