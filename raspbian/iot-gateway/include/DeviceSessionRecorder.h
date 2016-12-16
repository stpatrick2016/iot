#ifndef DEVICESESSIONRECORDER_H
#define DEVICESESSIONRECORDER_H

#include "ICommunicator.h"
#include "deviceinfo.h"

class DeviceSessionRecorder
{
    public:
        DeviceSessionRecorder(ICommunicator* communicator, DeviceInfo* device);

        bool Record();

    protected:
    private:
        ICommunicator* _communicator;
        DeviceInfo* _device;
};

#endif // DEVICESESSIONRECORDER_H
