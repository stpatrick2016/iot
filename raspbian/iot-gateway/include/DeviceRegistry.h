#ifndef DEVICEREGISTRY_H
#define DEVICEREGISTRY_H

#include <list>
#include "deviceinfo.h"
#include "ICommunicator.h"

using namespace std;

typedef list<DeviceInfo*> t_devices_list;

class DeviceRegistry
{
    public:
        DeviceRegistry();
        virtual ~DeviceRegistry();

        void loadKnownDevices();
        void reset();
        t_device_id connectNext(ICommunicator* pCommunicator);
    protected:
    private:
        t_devices_list _devices;
        t_devices_list::iterator _currentlyConnected;
};

#endif // DEVICEREGISTRY_H
