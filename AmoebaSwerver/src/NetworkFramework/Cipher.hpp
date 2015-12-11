class Cipher : public StringWare
{
protected:
    Cipher() {}

public:

    virtual string encrypt(string& dataStream) = 0;
    virtual string decrypt(string& dataStream) = 0;

    // Part of the MiddleWare interface
    string processInput(string& dataStream)
    {
        return decrypt(dataStream);
    }

    string processOutput(string& dataStream)
    {
        return encrypt(dataStream);
    }
};
