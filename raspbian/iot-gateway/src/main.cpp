#include "easylogging++.h"
#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <inttypes.h>
#include "DeviceRegistry.h"
#include "RF24Communicator.h"
#include "DeviceSessionRecorder.h"
#include "AddressPool.h"

INITIALIZE_EASYLOGGINGPP

//using namespace std;

DeviceRegistry* g_devices = NULL;
ICommunicator* g_communicator = NULL;
volatile bool g_continue = true;
volatile bool g_isVisiting = false;

void signal_ctrlbrk_handler(int s)
{
    if(s == SIGINT)
    {
        g_continue = false;
    }
}

void signal_alarm_handler(int sig)
{
    if(sig != SIGALRM || !__sync_bool_compare_and_swap(&g_isVisiting, false, true))
    {
        return; //previous run still not completed
    }

    t_devices_list devices;
    devices.push_back(new DeviceInfo(1, 0x1234567801LL, 0));
    //devices.push_back(new DeviceInfo(2, 0xCDEDEDED21LL, 0));

    for(t_devices_list::iterator it = devices.begin(); it != devices.end(); it++)
    {
        DeviceInfo* device = *it;
        DeviceSessionRecorder session(g_communicator, device);
        session.Record();
    }

    __sync_bool_compare_and_swap(&g_isVisiting, true, false);
}

int main(int argc, char* argv[])
{
    START_EASYLOGGINGPP(argc, argv);
    el::Configurations defaultConf;
    defaultConf.setToDefault();
    defaultConf.set(el::Level::Info, el::ConfigurationType::Enabled, "true");
    defaultConf.set(el::Level::Info, el::ConfigurationType::ToStandardOutput, "true");
    el::Loggers::reconfigureLogger("default", defaultConf);

    int exitCode = 0;
    signal(SIGINT, signal_ctrlbrk_handler);
    signal(SIGALRM, signal_alarm_handler);

    g_communicator = new RF24Communicator();
    //g_devices = new DeviceRegistry(g_communicator);
    try
    {
        //g_devices->loadKnownDevices();
        g_communicator->initialize();
        //alarm(10);
        while(1)
        {
            if(!g_continue)
            {
                cout << "Stop signal received." << endl;
                exitCode = 0;
                break;
            }
            //loop();
            signal_alarm_handler(SIGALRM);
            usleep(100);
        }
    }
    catch(exception& e)
    {
        cout << e.what() << endl;
        exitCode = -1;
    }
    catch(...)
    {
        cout << "FATAL Error" << endl;
        exitCode = -1;
    }

    delete g_devices;
    delete (RF24Communicator*)g_communicator;

    return exitCode;
}
