class AmoebaNetworkServerController : public NetworkServerController
{
public:
    AmoebaInterpreter interpreter;
    AmoebaCodec codec;

    AmoebaNetworkServerController(int maxConnections, int port)
    :   NetworkServerController(maxConnections, port, interpreter, codec)
    {
//        stringWareContainer.add(new DataStreamLogger("", true, false, true));
//        pairWareContainer.add(new KeyValuePairLogger("", true, false, true));
    }
};
