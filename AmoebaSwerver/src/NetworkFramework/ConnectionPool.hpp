class ConnectionPool
{
private:
    int nextConnectionId;
    deque<Connection> connections;

public:
    int maxConnections;

    ConnectionPool(int maxConnections = 10)
    {
        this->maxConnections = maxConnections;
        add(maxConnections);
        nextConnectionId = 0;
    }

    int size()
    {
        return connections.size();
    }

    bool add()
    {
        if (connections.size() < maxConnections)
        {
            Connection newConnection;
            newConnection.connectionId = nextConnectionId;
            nextConnectionId++;
            connections.push_back(newConnection);
            return true;
        }
        return false;
    }

    bool add(int count)
    {
        bool ret = true;
        for (int i = 0; ret && i < count; i++)
        {
            ret = add();
        }
        return ret;
    }

    void remove(int index)
    {
        if (connections.size() != 0)
        {
            connections[index].disconnect();
            connections.erase(connections.begin() + index);
        }
    }

    Connection& getConnection(int index)
    {
        return connections[index];
    }

    Connection* getConnectionById(int connectionId)
    {
        for (int i = 0; i < connections.size(); i++)
        {
            if (connections[i].connectionId == connectionId)
            {
                return &connections[i];
            }
        }
        return NULL;
    }
};
