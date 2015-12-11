struct NetworkMessage
{
    int connectionId;
    const string type;

protected:

    NetworkMessage(string type) : type(type) {}
};
