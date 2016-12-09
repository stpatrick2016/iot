#include "RF24Communicator.h"

RF24Communicator::RF24Communicator()
{
    _pRadio = new RF24(RPI_V2_GPIO_P1_15, RPI_V2_GPIO_P1_24, BCM2835_SPI_SPEED_8MHZ);
}

RF24Communicator::~RF24Communicator()
{
    delete _pRadio;
}

void RF24Communicator::initialize()
{
    _pRadio->begin();
    _pRadio->setRetries(15,15);
    _pRadio->setChannel(1);
    _pRadio->setDataRate(RF24_250KBPS);
    _pRadio->setPALevel(RF24_PA_MIN);
    _pRadio->setPayloadSize(sizeof(Payload));
    //_pRadio->openWritingPipe(pipes[0]);
    //_pRadio->openReadingPipe(1, pipes[1]);
    _pRadio->setAutoAck(1);
    //_pRadio->startListening();
    _pRadio->printDetails();
}

bool RF24Communicator::read(Payload* pPayload)
{
    if(_pRadio->available())
    {
        _pRadio->read(pPayload, sizeof(Payload));
        return true;
    }
    return false;
}

void RF24Communicator::connectRead(vn_pipe_id pipe)
{
    _pRadio->stopListening();
    _pRadio->openReadingPipe(1, pipe);
    _pRadio->startListening();
}

void RF24Communicator::connectWrite(vn_pipe_id pipe)
{
    _pRadio->openWritingPipe(pipe);
}

