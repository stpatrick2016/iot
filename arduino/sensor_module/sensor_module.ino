#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "payload.h"


Payload msg;
const uint64_t pipe = 0xFDADADAD02LL;
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
  radio.openWritingPipe(pipe);
  //radio.startListening();
  radio.printDetails();
  radio.powerUp();
}

void loop() {
  msg.type = PayloadType::METEO;
  msg.data.meteo.temperature = 32;
  Serial.print("Sending temperature... ");
  if(radio.write(&msg, sizeof(msg)))
  {
    printf("ok\n");
  }
  else
  {
    printf("fail\n");
  }

  delay(2000);
}
