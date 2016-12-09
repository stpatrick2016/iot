#include <iostream>
#include <unistd.h>
#include "RF24/RF24.h"
#include "payload.h"

using namespace std;

//RF24 radio(RPI_V2_GPIO_P1_16, RPI_V2_GPIO_P1_26, BCM2835_SPI_SPEED_8MHZ);
RF24 radio(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ);
const uint64_t pipes[2] = {0xFDADADAD01LL, 0xFDADADAD02LL};

Payload payload = Payload();

void setup(void)
{
    radio.begin();
    radio.setRetries(15,15);
    radio.setChannel(1);
    radio.setDataRate(RF24_250KBPS);
    radio.setPALevel(RF24_PA_MIN);
    radio.setPayloadSize(sizeof(payload));
    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1, pipes[1]);
    radio.setAutoAck(1);
    radio.startListening();
    radio.printDetails();
}

void loop(void)
{
    uint8_t pipeNum = -1;
    if(radio.available(&pipeNum) && pipeNum > 0)
    {
        printf("Reading data from pipe %d\n", pipeNum);
        radio.read(&payload, sizeof(payload));
        printf("packet %d \n", payload.data.meteo.temperature);
        fflush(stdout);
    }
    else
    {
        usleep(100);
    }
}

int main()
{
    int exitCode = 0;
    try{
        setup();
        while(1)
        {
            loop();
        }
    }
    catch(exception& e)
    {
        cout << e.what() << '\n';
    }
    catch(...)
    {
        cout << "FATAL Error \n";
        exitCode = -1;
    }
    return exitCode;
}
