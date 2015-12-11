class MessageWareContainer
{
private:
    deque<MessageWare*> middleWares;
public:

    void add(MessageWare& middleWare)
    {
        middleWares.push_back(&middleWare);
    }

    void add(MessageWare* middleWare)
    {
        middleWares.push_back(middleWare);
    }

    deque<NetworkMessage*> processForInput(deque<NetworkMessage*>& messages, int connectionId)
    {
        for (int i = 0; i < middleWares.size(); i++)
        {
            deque<NetworkMessage*> processedMessages = middleWares[i]->processInput(messages, connectionId);
            messages.clear();
            for (int i = 0; i < processedMessages.size(); i++)
            {
                messages.push_back(processedMessages[i]);
            }
        }
        return messages;
    }

    deque<NetworkMessage*> processForOutput(deque<NetworkMessage*>& messages, int connectionId)
    {
        for (int i = middleWares.size() - 1; i >= 0; i--)
        {
            deque<NetworkMessage*> processedMessages = middleWares[i]->processOutput(messages, connectionId);
            messages.clear();
            for (int i = 0; i < processedMessages.size(); i++)
            {
                messages.push_back(processedMessages[i]);
            }
        }
        return messages;
    }
};
