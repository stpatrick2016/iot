#include <unistd.h>
#include <iostream>

#include "DeviceSessionRecorder.h"
#include "AddressPool.h"

using namespace std;

DeviceSessionRecorder::DeviceSessionRecorder(ICommunicator* communicator, DeviceInfo* device)
{
    _communicator = communicator;
    _device = device;
}

bool DeviceSessionRecorder::Record()
{
    if(_device == NULL)
    {
        return false;
    }

    bool ret = false;
    if(_device->local_pipe == 0)
    {
        _device->local_pipe = AddressPool::Instance().GetAddress();
    }
    _communicator->connectWrite(_device->remote_pipe);
    _communicator->connectRead(&(_device->local_pipe), 1);

    Payload data;
    data.type = PayloadType::DATA_REQUEST;
    data.data.address = _device->local_pipe;
    if(_communicator->write(&data))
    {
        if(_communicator->read(&data))
        {
            if(data.type == PayloadType::METEO)
            {
                cout << "Meteo data received. Temp: " << data.data.meteo.temperature << endl;
            }
            else if(data.type == PayloadType::RESPONSE_COMPLETED)
            {
                cout << "Data transmission completed" << endl;
            }
        }
        else
        {
            cout << "Didn't receive reply from device " << (_device->Id) << endl;
        }
    }
    else
    {
        cout << "Unable to send data to device " << (_device->Id) << endl;
    }

    AddressPool::Instance().ReleaseAddress(_device->local_pipe);

    return ret;
}

