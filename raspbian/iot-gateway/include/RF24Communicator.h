#ifndef RF24COMMUNICATOR_H
#define RF24COMMUNICATOR_H

#include "RF24.h"
#include <ICommunicator.h>

class RF24Communicator : public ICommunicator
{
    public:
        /** Default constructor */
        RF24Communicator();
        /** Default destructor */
        virtual ~RF24Communicator();

        void initialize();
        bool read(Payload* pPayload);
        void connectRead(int count, ...);
        void connectWrite(vn_pipe_id pipe);

    protected:
    private:
        RF24* _pRadio;
};

#endif // RF24COMMUNICATOR_H
