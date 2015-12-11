class CompressionAlgorithm : public StringWare
{
protected:
    CompressionAlgorithm() {}

public:

    virtual string compress(string& dataStream) = 0;
    virtual string decompress(string& dataStream) = 0;

    // Part of the MiddleWare interface
    string processInput(string& dataStream)
    {
        return decompress(dataStream);
    }

    string processOutput(string& dataStream)
    {
        return compress(dataStream);
    }
};
