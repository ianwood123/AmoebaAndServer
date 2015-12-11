class CommandFactory
{
private:
    GameWorld &gameWorld;
    ConnectionPool& connectionPool;
    NetworkMessageMailer& mailer;

public:

    CommandFactory(GameWorld& gameWorld, ConnectionPool& connectionPool, NetworkMessageMailer& mailer)
    :   gameWorld(gameWorld), connectionPool(connectionPool), mailer(mailer) {}

    deque<Command*> generateCommands(deque<NetworkMessage*> messages)
    {
        deque<Command*> commands = lookupCommands(messages);
        return commands;
    }

private:

    deque<Command*> lookupCommands(deque<NetworkMessage*> messages)
    {
        deque<Command*> commands;
        for (int i = 0; i < messages.size(); i++)
        {
            NetworkMessage& message = *messages[i];
            string messageType = message.type;
            if (messageType == "PlainTextMessage")
            {
                PlainTextMessage& m = (PlainTextMessage&)message;
                commands.push_back(new DisplayPlainTextCommand(m.text));
                delete &m;
            }
            else if (messageType == "NewConnectionMessage")
            {
                NewConnectionMessage& m = (NewConnectionMessage&)message;
                commands.push_back(new CheckLoginConnectionCommand(m));
                delete &m;
            }
            else if (messageType == "ConnectionTimeoutMessage")
            {
                ConnectionTimeoutMessage& m = (ConnectionTimeoutMessage&)message;
                commands.push_back(new RemovePlayerCommand(gameWorld, m, connectionPool));
                delete &m;
            }
            else if (messageType == "LoginMessage")
            {
                LoginMessage& m = (LoginMessage&)message;
                commands.push_back(new LoginCommand(gameWorld, m, mailer));
                delete &m;
            }
            else if (messageType == "LogoutMessage")
            {
                LogoutMessage& m = (LogoutMessage&)message;
                commands.push_back(new RemovePlayerCommand(gameWorld, m, connectionPool));
                delete &m;
            }
            else if (messageType == "MoveInDirectionMessage")
            {
                MoveInDirectionMessage& m = (MoveInDirectionMessage&)message;
                commands.push_back(new MoveBlobCommand(gameWorld, m));
                delete &m;
            }
            else if (messageType == "MoveTowardCoordinatesMessage")
            {
                MoveTowardCoordinatesMessage& m = (MoveTowardCoordinatesMessage&)message;
                commands.push_back(new MoveTowardCoordinatesCommand(gameWorld, m));
                delete &m;
            }
            else if (messageType == "ChatMessage")
            {
                ChatMessage& m = (ChatMessage&)message;
                commands.push_back(new SendChatMessageCommand(mailer, gameWorld, m));
                delete &m;
            }
        }
        return commands;
    }
};
