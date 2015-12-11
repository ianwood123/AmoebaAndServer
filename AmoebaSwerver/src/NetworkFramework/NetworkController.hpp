class NetworkController
{
protected:
    StringWareContainer stringWareContainer;
    PairWareContainer pairWareContainer;
    MessageWareContainer messageWareContainer;

    NetworkController(int maxConnections, Interpreter& interpreter, Codec& codec, int connectionTimeout)
        :   connectionPool(ConnectionPool(maxConnections)),
            receiver(*new ReceiverThread(connectionPool, incomingMailer, messageWareContainer, interpreter, pairWareContainer, codec, stringWareContainer, connectionTimeout)),
            sender(*new SenderThread(connectionPool, outgoingMailer, messageWareContainer, interpreter, pairWareContainer, codec, stringWareContainer)) {}

public:
    ConnectionPool connectionPool;
    NetworkMessageMailer incomingMailer;
    NetworkMessageMailer outgoingMailer;

    ReceiverThread& receiver;
    SenderThread& sender;

    virtual void start()
    {
        receiver.start(Thread::infiniteLoop);
        sender.start(Thread::infiniteLoop);
    }

    virtual void stop()
    {
        sender.stop();
        receiver.stop();
    }
};
