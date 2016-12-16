#ifndef ICOMMUNICATOR_H_INCLUDED
#define ICOMMUNICATOR_H_INCLUDED

#include "payload.h"
#include "deviceinfo.h"

class ICommunicator
{
    public:
        virtual void initialize() = 0;
        virtual bool read(Payload* pPayload) = 0;
        virtual bool write(Payload* payload) = 0;
        virtual void connectRead(vn_pipe_id* pipes, int count) = 0;
        virtual void connectWrite(vn_pipe_id pipe) = 0;
};

#endif // ICOMMUNICATOR_H_INCLUDED
