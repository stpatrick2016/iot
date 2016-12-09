#ifndef DEVICEINFO_H_INCLUDED
#define DEVICEINFO_H_INCLUDED

#include <stdint.h>

typedef uint16_t vn_deviceinfo_version;
typedef uint64_t vn_pipe_id;
typedef uint64_t t_device_id;

class DeviceInfo
{
public:
    DeviceInfo()
    {
        version = 1;
    }

    DeviceInfo(t_device_id id, vn_pipe_id remotePipe, vn_pipe_id localPipe)
    :DeviceInfo()
    {
        Id = id;
        remote_pipe = remotePipe;
        local_pipe = localPipe;
    }

    vn_deviceinfo_version version;
    t_device_id Id;
    vn_pipe_id remote_pipe; //this is pipe where we will write to
    vn_pipe_id local_pipe; //this is pipe on which we will listen
};


#endif // DEVICEINFO_H_INCLUDED
