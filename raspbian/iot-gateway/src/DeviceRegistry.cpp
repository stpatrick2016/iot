#include "DeviceRegistry.h"

DeviceRegistry::DeviceRegistry()
{
    //ctor
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
