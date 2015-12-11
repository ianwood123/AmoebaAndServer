class AmoebaInterpreter : public Interpreter
{
public:

    deque<NetworkMessage*> parse(deque<KeyValuePair>& pairs)
    {
        int beginSection = 0;
        int endSection = 0;
        deque<NetworkMessage*> messages;
        for (int i = 0; i < pairs.size(); i++)
        {
            KeyValuePair pair = pairs[i];
            if (pair.field == "begin")
            {
                beginSection = i;
            }
            else if (pair.field == "end")
            {
                endSection = i;
                parseSection(beginSection, endSection, pairs, messages);
            }
        }
        return messages;
    }

    deque<KeyValuePair> compile(deque<NetworkMessage*>& messages)
    {
        deque<KeyValuePair> pairs;
        for (int i = 0; i < messages.size(); i++)
        {
            compileMessage(messages[i], pairs);
        }
        return pairs;
    }

private:

    void parseSection(int begin, int end, const deque<KeyValuePair>& pairs, deque<NetworkMessage*>& messages)
    {
        string messageType = pairs[begin].value;
        if (messageType == "PlainTextMessage")
        {
            string text = getValue("text", begin, end, pairs);
            messages.push_back(new PlainTextMessage(text));
        }
        else if (messageType == "LoginMessage")
        {
            string username = getValue("username", begin, end, pairs);
            string password = getValue("password", begin, end, pairs);
            messages.push_back(new LoginMessage(username, password));
        }
        else if (messageType == "LogoutMessage")
        {
            messages.push_back(new LogoutMessage());
        }
        else if (messageType == "MoveTowardCoordinatesMessage")
        {
            double x = toDouble(getValue("x", begin, end, pairs));
            double y = toDouble(getValue("y", begin, end, pairs));
            messages.push_back(new MoveTowardCoordinatesMessage(x, y));
        }
        else if (messageType == "MoveInDirectionMessage")
        {
            double direction = toDouble(getValue("direction", begin, end, pairs));
            messages.push_back(new MoveInDirectionMessage(direction));
        }
        else if (messageType == "SetBlobPropertiesMessage")
        {
            deque<KeyValuePair> properties;
            properties.push_back(KeyValuePair("color", getValue("color", begin, end, pairs)));
            messages.push_back(new SetBlobPropertiesMessage(properties));
        }
        else if (messageType == "PelletPositionMessage")
        {
            double x = toDouble(getValue("x", begin, end, pairs));
            double y = toDouble(getValue("y", begin, end, pairs));
            long id = toLong(getValue("id", begin, end, pairs));
            messages.push_back(new PelletPositionMessage(x, y, id));
        }
        else if (messageType == "BlobStateMessage")
        {
            deque<KeyValuePair> properties;
            properties.push_back(KeyValuePair("id", getValue("id", begin, end, pairs)));
            properties.push_back(KeyValuePair("x", getValue("x", begin, end, pairs)));
            properties.push_back(KeyValuePair("y", getValue("y", begin, end, pairs)));
            properties.push_back(KeyValuePair("size", getValue("size", begin, end, pairs)));
            properties.push_back(KeyValuePair("color", getValue("color", begin, end, pairs)));
            properties.push_back(KeyValuePair("username", getValue("username", begin, end, pairs)));
            messages.push_back(new BlobStateMessage(properties));
        }
        else if (messageType == "ChatMessage")
        {
            string username = getValue("username", begin, end, pairs);
            string text = getValue("text", begin, end, pairs);
            messages.push_back(new ChatMessage(username, text));
        }
    }

    void compileMessage(NetworkMessage *message, deque<KeyValuePair>& pairs)
    {
        string messageType = message->type;
        if (messageType == "PlainTextMessage")
        {
            PlainTextMessage& m = (PlainTextMessage&)*message;
            pairs.push_back(KeyValuePair("begin", messageType));
            pairs.push_back(KeyValuePair("text", m.text));
            pairs.push_back(KeyValuePair("end", messageType));
            delete &m;
        }
        else if (messageType == "LoginMessage")
        {
            LoginMessage& m = (LoginMessage&)*message;
            pairs.push_back(KeyValuePair("begin", messageType));
            pairs.push_back(KeyValuePair("username", m.username));
            pairs.push_back(KeyValuePair("password", m.password));
            pairs.push_back(KeyValuePair("end", messageType));
            delete &m;
        }
        else if (messageType == "LogoutMessage")
        {
            LogoutMessage& m = (LogoutMessage&)*message;
            pairs.push_back(KeyValuePair("begin", messageType));
            pairs.push_back(KeyValuePair("end", messageType));
            delete &m;
        }
        else if (messageType == "BlobStateMessage")
        {
            BlobStateMessage& m = (BlobStateMessage&)*message;
            pairs.push_back(KeyValuePair("begin", messageType));
            for (int i = 0; i < m.properties.size(); i++)
            {
                pairs.push_back(KeyValuePair(m.properties[i].field, m.properties[i].value));
            }
            pairs.push_back(KeyValuePair("end", messageType));
            delete &m;
        }
        else if (messageType == "PelletPositionMessage")
        {
            PelletPositionMessage& m = (PelletPositionMessage&)*message;
            pairs.push_back(KeyValuePair("begin", messageType));
            pairs.push_back(KeyValuePair("x", toString(m.x)));
            pairs.push_back(KeyValuePair("y", toString(m.y)));
            pairs.push_back(KeyValuePair("id", toString(m.id)));
            pairs.push_back(KeyValuePair("end", messageType));
            delete &m;
        }
        else if (messageType == "MoveInDirectionMessage")
        {
            MoveInDirectionMessage& m = (MoveInDirectionMessage&)*message;
            pairs.push_back(KeyValuePair("begin", messageType));
            pairs.push_back(KeyValuePair("direction", toString(m.direction)));
            pairs.push_back(KeyValuePair("end", messageType));
            delete &m;
        }
        else if (messageType == "MoveTowardCoordinatesMessage")
        {
            MoveTowardCoordinatesMessage& m = (MoveTowardCoordinatesMessage&)*message;
            pairs.push_back(KeyValuePair("begin", messageType));
            pairs.push_back(KeyValuePair("x", toString(m.x)));
            pairs.push_back(KeyValuePair("y", toString(m.y)));
            pairs.push_back(KeyValuePair("end", messageType));
            delete &m;
        }
        else if (messageType == "ChatMessage")
        {
            ChatMessage& m = (ChatMessage&)*message;
            pairs.push_back(KeyValuePair("begin", messageType));
            pairs.push_back(KeyValuePair("username", m.username));
            pairs.push_back(KeyValuePair("text", m.text));
            pairs.push_back(KeyValuePair("end", messageType));
            delete &m;
        }
    }

    string getValue(string field, int begin, int end, const deque<KeyValuePair>& pairs)
    {
        for (int i = begin; i < end; i++)
        {
            if (pairs[i].field == field)
            {
                return pairs[i].value;
            }
        }
        return "";
    }
};
