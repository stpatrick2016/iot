#include "DeviceRegistry.h"
#include <unistd.h>

DeviceRegistry::DeviceRegistry()
{
    _currentlyConnected = _devices.begin();
}

DeviceRegistry::~DeviceRegistry()
{
    reset();
}

void DeviceRegistry::loadKnownDevices()
{
    DeviceInfo* pDevice = new DeviceInfo();
    pDevice->remote_pipe = 0xEDEDEDED01LL;
    pDevice->local_pipe = 0xFDADADAD02LL;
    _devices.push_back(pDevice);
}

void DeviceRegistry::reset()
{
    for(t_devices_list::iterator it=_devices.begin(); it != _devices.end(); it++)
    {
        delete (DeviceInfo*)*it;
    }

    _devices.clear();
}

void DeviceRegistry::connectNext(ICommunicator* pCommunicator)
{
    if(!_devices.empty())
    {
        if(_currentlyConnected == _devices.end())
        {
            _currentlyConnected = _devices.begin();
        }

        DeviceInfo* pDevice = *_currentlyConnected;
        pCommunicator->connectWrite(pDevice->remote_pipe);
        pCommunicator->connectRead(pDevice->local_pipe);
        usleep(1000);

        _currentlyConnected++;
    }
}
