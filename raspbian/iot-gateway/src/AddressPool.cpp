#include <mutex>
#include "AddressPool.h"

AddressPool* AddressPool::_instance = NULL;
t_device_id AddressPool::_lastUsedAddress = 0x6000000001LL;
std::mutex g_addressPoolGuard;
std::mutex g_addressPoolInstanceGuard;

AddressPool::AddressPool()
{
    //ctor
}

AddressPool& AddressPool::Instance()
{
    if(_instance == NULL)
    {
        std::lock_guard<std::mutex> guard(g_addressPoolInstanceGuard);
        if(_instance == NULL)
        {
            _instance = new AddressPool();
        }
    }

    return *_instance;
}

t_device_id AddressPool::GetAddress()
{
    std::lock_guard<std::mutex> guard(g_addressPoolGuard);

    if(AddressPool::_lastUsedAddress < 0x6000000000LL)
    {
        AddressPool::_lastUsedAddress = 0x6000000000LL ;
    }

    return ++AddressPool::_lastUsedAddress;
}

void AddressPool::ReleaseAddress(t_device_id id)
{
    //we do nothing at this moment. TBD later
}
