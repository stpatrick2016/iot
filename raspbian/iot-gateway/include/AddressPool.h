#ifndef ADDRESSPOOL_H
#define ADDRESSPOOL_H

#include "deviceinfo.h"

class AddressPool
{
    public:
        static AddressPool& Instance();

        t_device_id GetAddress();
        void ReleaseAddress(t_device_id id);
    protected:
    private:
        AddressPool();

        static AddressPool* _instance;
        static t_device_id _lastUsedAddress;
};

#endif // ADDRESSPOOL_H
