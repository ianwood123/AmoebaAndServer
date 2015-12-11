class NetworkServerController : public NetworkController
{
protected:
    NetworkServerController(int maxConnections, int port, Interpreter& interpreter, Codec& codec, int connectionTimeout = 1000)
        :   NetworkController(maxConnections, interpreter, codec, connectionTimeout),
            connector(*new ConnectorThread(connectionPool, incomingMailer, port)) {}

public:
    ConnectorThread& connector;

    void start()
    {
        connector.start(Thread::infiniteLoop);
        NetworkController::start();
    }

    void stop()
    {
        connector.stop();
        NetworkController::stop();
    }
};
