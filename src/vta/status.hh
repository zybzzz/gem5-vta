#ifndef STATUS_HH
#define STATUS_HH

namespace gem5
{

enum class Status
{
    Idle,
    Running,
    Faulting,
    ITBWaitResponse,
    IcacheRetry,
    IcacheWaitResponse,
    IcacheWaitSwitch,
    DTBWaitResponse,
    DcacheRetry,
    DcacheWaitResponse,
    DcacheWaitSwitch,
};

}

#endif
