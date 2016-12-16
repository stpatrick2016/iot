#include "DeviceRegistry.h"

DeviceRegistry::DeviceRegistry(ICommunicator* communicator)
{
    _currentlyConnected = _devices.begin();
    _communicator = communicator;
}

DeviceRegistry::~DeviceRegistry()
{
    reset();
}

void DeviceRegistry::loadKnownDevices()
{
    _devices.push_back(new DeviceInfo(1, 0xEDEDEDED01LL, 0xFDADADAD02LL));
    _devices.push_back(new DeviceInfo(2, 0xEDEDEDED01LL, 0xFDADADAD03LL));
    _devices.push_back(new DeviceInfo(3, 0xEDEDEDED01LL, 0xFDADADAD04LL));
    _devices.push_back(new DeviceInfo(4, 0xEDEDEDED01LL, 0xFDADADAD05LL));
    _devices.push_back(new DeviceInfo(5, 0xEDEDEDED01LL, 0xFDADADAD06LL));
}

void DeviceRegistry::reset()
{
    for(t_devices_list::iterator it=_devices.begin(); it != _devices.end(); it++)
    {
        delete (DeviceInfo*)*it;
    }

    _devices.clear();
}

t_device_id DeviceRegistry::connectNext()
{
    t_device_id ret = 0;
    if(!_devices.empty())
    {
        if(_currentlyConnected == _devices.end())
        {
            _currentlyConnected = _devices.begin();
        }
        const int maxToConnect = 5;
        int totalConnected = 0;
        vn_pipe_id pipes[maxToConnect] = {0};
        while(_currentlyConnected != _devices.end() && totalConnected < maxToConnect)
        {
            DeviceInfo* pDevice = *_currentlyConnected;
            pipes[totalConnected] =  pDevice->local_pipe;

            _currentlyConnected++;
            totalConnected++;
        }

        _communicator->connectRead(pipes, totalConnected);

        _currentlyConnected++;
    }

    return ret;
}

void DeviceRegistry::sendServerAddress(t_device_id deviceId)
{
}
