class AmoebaNetworkClientController : public NetworkClientController
{
public:
    AmoebaInterpreter interpreter;
    AmoebaCodec codec;

    AmoebaNetworkClientController(int maxConnections = 1)
        : NetworkClientController(maxConnections, interpreter, codec)
    {
    }

    bool connect(string address, int port)
    {
        if (connectionPool.getConnection(0).connect(address, port, 3))
        {
            start();
            return true;
        }
        return false;
    }
};
