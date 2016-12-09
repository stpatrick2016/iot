#include "DeviceRegistry.h"

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
    _devices.push_back(new DeviceInfo(1, 0xEDEDEDED01LL, 0xFDADADAD02LL));
    _devices.push_back(new DeviceInfo(2, 0xEDEDEDED01LL, 0x1212121201LL));
    _devices.push_back(new DeviceInfo(3, 0xEDEDEDED01LL, 0x2212121201LL));
    _devices.push_back(new DeviceInfo(4, 0xEDEDEDED01LL, 0x3212121201LL));
    _devices.push_back(new DeviceInfo(5, 0xEDEDEDED01LL, 0x4212121201LL));
}

void DeviceRegistry::reset()
{
    for(t_devices_list::iterator it=_devices.begin(); it != _devices.end(); it++)
    {
        delete (DeviceInfo*)*it;
    }

    _devices.clear();
}

t_device_id DeviceRegistry::connectNext(ICommunicator* pCommunicator)
{
    t_device_id ret = 0;
    if(!_devices.empty())
    {
        if(_currentlyConnected == _devices.end())
        {
            _currentlyConnected = _devices.begin();
        }

        DeviceInfo* pDevice = *_currentlyConnected;
        ret = pDevice->Id;
        pCommunicator->connectWrite(pDevice->remote_pipe);
        pCommunicator->connectRead(pDevice->local_pipe);

        _currentlyConnected++;
    }

    return ret;
}
