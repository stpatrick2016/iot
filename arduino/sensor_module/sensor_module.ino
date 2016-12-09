#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "payload.h"


Payload msg;
const uint64_t pipes[] = {0xFDADADAD02LL, 0x1212121201LL, 0x2212121201LL, 0x3212121201LL, 0x4212121201LL};
const unsigned long timeoutPeriod = 3000;
RF24 radio(9,10);
FILE serial_stdout;

int serial_putchar(char c, FILE* f) {
   if (c == '\n') serial_putchar('\r', f);
   return Serial.write(c) == 1? 0 : 1;
}

void setup() {
  Serial.begin(9600);
  // Set up stdout
  fdev_setup_stream(&serial_stdout, serial_putchar, NULL, _FDEV_SETUP_WRITE);
  stdout = &serial_stdout;
  
  msg.version = 1;

  printf("Starting...\n");
  radio.begin();
  radio.setChannel(1);
  radio.setDataRate(RF24_250KBPS);
  radio.setPALevel(RF24_PA_HIGH);
  radio.setAutoAck(1);
  radio.setRetries(2,15);
  radio.setPayloadSize(sizeof(msg));
  //radio.startListening();
  radio.printDetails();
  radio.powerUp();
}

void loop() {

  for(int i=0; i<(sizeof(pipes) / sizeof(uint64_t)); i++)
  {
    msg.type = PayloadType::METEO;
    msg.data.meteo.temperature = 32;
    printf("Sending temperature to %d... ", i);
    radio.openWritingPipe(pipes[i]);
    if(radio.write(&msg, sizeof(msg)))
    {
      printf("ok\n");
    }
    else
    {
      printf("fail\n");
    }
  }
  delay(2000);
}
