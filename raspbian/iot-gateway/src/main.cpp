#include <iostream>
#include <unistd.h>
#include <signal.h>
#include <inttypes.h>
#include "DeviceRegistry.h"
#include "RF24Communicator.h"

using namespace std;

Payload payload = Payload();
DeviceRegistry devices;
ICommunicator* g_communicator = NULL;
volatile bool g_continue = true;

void signal_handler(int s)
{
    g_continue = false;
}

void loop(void)
{
    t_device_id deviceId = devices.connectNext(g_communicator);
    usleep(1000); //wait for buffer to fill up if anything goes there.
    if(g_communicator->read(&payload))
    {
        printf("packet from %" PRIu64 ": temp %d \n", deviceId, payload.data.meteo.temperature);
    }
}

int main()
{
    int exitCode = 0;
    signal(SIGINT, signal_handler);
    g_communicator = new RF24Communicator();
    try
    {
        devices.loadKnownDevices();
        g_communicator->initialize();
        while(1)
        {
            if(!g_continue)
            {
                cout << "Stop signal received." << endl;
                exitCode = 0;
                break;
            }
            loop();
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

    devices.reset();
    delete (RF24Communicator*)g_communicator;

    return exitCode;
}
