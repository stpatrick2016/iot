#ifndef DEVICEREGISTRY_H
#define DEVICEREGISTRY_H

#include <list>
#include "deviceinfo.h"

using namespace std;

typedef list<DeviceInfo*> t_devices_list;

class DeviceRegistry
{
    public:
        DeviceRegistry();
        virtual ~DeviceRegistry();

        void loadKnownDevices();
        void reset();
    protected:
    private:
        t_devices_list _devices;
};

#endif // DEVICEREGISTRY_H
