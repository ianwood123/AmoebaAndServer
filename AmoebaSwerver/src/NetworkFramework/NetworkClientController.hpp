class NetworkClientController : public NetworkController
{
protected:
    NetworkClientController(int maxConnections, Interpreter& interpreter, Codec& codec, int connectionTimeout = 1000)
        :   NetworkController(maxConnections, interpreter, codec, connectionTimeout) {}

public:

    virtual bool connect(string address, int port) = 0;
};
