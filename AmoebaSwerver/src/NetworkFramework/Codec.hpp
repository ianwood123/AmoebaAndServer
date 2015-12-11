class Codec
{
protected:
    Codec() {}

public:

    virtual bool checkBeginStream(string& data, Connection& connection) = 0;
    virtual bool checkEndStream(string& data) = 0;

    virtual deque<KeyValuePair> decode(string& dataStream) = 0;
    virtual string encode(deque<KeyValuePair>& pairs) = 0;
};
