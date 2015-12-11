class Connection
{
private:
    ClientSocket* clientSocket;
    ServerSocket* serverSocket;
    bool server;
    bool client;

public:
    int connectionId;
    int inactiveTime;

    Connection()
    {
        server = false;
        client = false;
        inactiveTime = 0;
        connectionId = -1;
    }

    void sendData(string data)
    {
        if (server)
        {
            serverSocket->sendData(data);
        }
        else if (client)
        {
            clientSocket->sendData(data);
        }
    }

    string getData()
    {
        string data = "";
        if (server)
        {
            data += serverSocket->getString();
            return data;
        }
        else if (client)
        {
            data += clientSocket->getString();
            return data;
        }
        return "";
    }

    bool isConnected()
    {
        if (server)
        {
            return serverSocket->isConnected();
        }
        else if (client)
        {
            return clientSocket->isConnected();
        }
        return false;
    }

    bool isActive()
    {
        if (server)
        {
            return serverSocket->isActive();
        }
        else if (client)
        {
            return clientSocket->isActive();
        }
        return false;
    }

    string getIpAddress()
    {
        if (server)
        {
            return serverSocket->getLocalAddress();
        }
        else if (client)
        {
            return clientSocket->getLocalAddress();
        }
        return "";
    }

    int getPort()
    {
        if (server)
        {
            return serverSocket->getPort();
        }
        else if (client)
        {
            return clientSocket->getPort();
        }
        return -1;
    }

    bool accept(int incomingPort, string address = "0")
    {
        server = true;
        client = false;
        inactiveTime = 0;
        serverSocket = new ServerSocket();
        return serverSocket->accept(incomingPort, address);
    }

    bool connect(string address, int incomingPort, int attempts = 3)
    {
        server = false;
        client = true;
        inactiveTime = 0;
        clientSocket = new ClientSocket();
        return clientSocket->connect(address, incomingPort, attempts);
    }

    void disconnect()
    {
        server = false;
        client = false;
        if (client)
        {
            clientSocket->disconnect();
            delete& clientSocket;
        }
        if (server)
        {
            serverSocket->disconnect();
            delete& serverSocket;
        }
    }
};
