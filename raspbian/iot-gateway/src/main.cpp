#include <iostream>
#include <unistd.h>
#include "DeviceRegistry.h"
#include "RF24Communicator.h"

using namespace std;

Payload payload = Payload();
DeviceRegistry devices;
ICommunicator* g_communicator = NULL;

void loop(void)
{
    devices.connectNext(g_communicator);
    if(g_communicator->read(&payload))
    {
        printf("packet %d \n", payload.data.meteo.temperature);
    }
    else
    {
        usleep(100);
    }
}

int main()
{
    int exitCode = 0;
    g_communicator = new RF24Communicator();
    try
    {
        devices.loadKnownDevices();
        g_communicator->initialize();
        while(1)
        {
            loop();
        }
    }
    catch(exception& e)
    {
        cout << e.what() << '\n';
        exitCode = -1;
    }
    catch(...)
    {
        cout << "FATAL Error \n";
        exitCode = -1;
    }

    devices.reset();
    delete (RF24Communicator*)g_communicator;

    return exitCode;
}
