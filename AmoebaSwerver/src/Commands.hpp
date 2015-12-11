class DisplayPlainTextCommand : public Command
{
private:
    string text;

public:

    DisplayPlainTextCommand(string text) : text(text) {}

    void execute()
    {
        cout << text << endl;
    }
};

class CheckLoginConnectionCommand : public Command
{
private:
    NewConnectionMessage m;

public:

    CheckLoginConnectionCommand(NewConnectionMessage m) : m(m) {}

    void execute()
    {
        cout << "New connection " <<m.connectionId << ' ' << m.ipAddress << ':' << toString(m.port) << endl;
        CheckLoginThread::startThread();
    }
};

class LoginCommand : public Command
{
private:
    GameWorld& gameWorld;
    NetworkMessageMailer& mailer;
    string username;
    string password;
    int connectionId;

public:

    LoginCommand(GameWorld& gameWorld, LoginMessage m, NetworkMessageMailer& mailer)
    :   gameWorld(gameWorld), mailer(mailer),
        username(m.username), password(m.password), connectionId(m.connectionId) {}

    void execute()
    {
        // Do authentication here later.
        if (gameWorld.findPlayerByConnectionId(connectionId) == NULL)
        {
            cout << "New player " << username << " on connection " << connectionId << endl;
            gameWorld.addPlayer(connectionId, connectionId, username);
        }
        else
        {
            mailer.push(connectionId, new LoginFailedMessage());
        }
    }
};

class RemovePlayerCommand : public Command
{
private:
    GameWorld& gameWorld;
    int connectionId;
    ConnectionPool& connectionPool;

public:

    RemovePlayerCommand(GameWorld& gameWorld, ConnectionTimeoutMessage m, ConnectionPool& connectionPool)
    :   gameWorld(gameWorld), connectionId(m.connectionId), connectionPool(connectionPool) {}

    RemovePlayerCommand(GameWorld& gameWorld, LogoutMessage m, ConnectionPool& connectionPool)
    :   gameWorld(gameWorld), connectionId(m.connectionId), connectionPool(connectionPool) {}

    void execute()
    {
        cout << "Disconnect connection " << connectionId << endl;
        connectionPool.getConnection(connectionId).disconnect();
        Player* player = gameWorld.findPlayerByConnectionId(connectionId);
        if (player != NULL)
        {
            cout << "Remove player " << player->playerId << " " << player->username << endl;
            gameWorld.removePlayerByConnectionId(connectionId);
        }
    }
};

class MoveBlobCommand : public Command
{
private:
    GameWorld& gameWorld;
    int connectionId;
    double direction;

public:

    MoveBlobCommand(GameWorld& gameWorld, MoveInDirectionMessage m)
    :   gameWorld(gameWorld), connectionId(m.connectionId), direction(m.direction) {}

    MoveBlobCommand(GameWorld& gameWorld, int connectionId, double direction)
    :   gameWorld(gameWorld), connectionId(connectionId), direction(direction) {}

    void execute()
    {
        Player* player = gameWorld.findPlayerByConnectionId(connectionId);
        if (player != NULL && &player->blob != NULL)
        {
            Blob& blob = player->blob;
            ViewWindow& window = player->window;
            window.centerWindow(blob.x, blob.y);
            blob.move(direction);
        }
    }
};

class MoveTowardCoordinatesCommand : public Command
{
private:
    GameWorld& gameWorld;
    int connectionId;
    double direction;
    double x, y;

public:

    MoveTowardCoordinatesCommand(GameWorld& gameWorld, MoveTowardCoordinatesMessage m)
    :   gameWorld(gameWorld), connectionId(m.connectionId), x(m.x), y(m.y) {}

    void execute()
    {
        Player* player = gameWorld.findPlayerByConnectionId(connectionId);
        if (player != NULL && &player->blob != NULL)
        {
            ViewWindow& window = player->window;
            Blob& blob = player->blob;
            degreeAngleBetweenPoints(window.serverToClientView(blob.getCenterPoint()), Point(x, window.length - y), direction);
            MoveBlobCommand mc(gameWorld, connectionId, direction);
            mc.execute();
        }
    }
};

class SendChatMessageCommand : public Command
{
private:
    int connectionId;
    NetworkMessageMailer& mailer;
    GameWorld& gameWorld;
    string username;
    string text;

public:
    SendChatMessageCommand (NetworkMessageMailer& mailer, GameWorld& gameWorld, ChatMessage message)
    :   connectionId(message.connectionId), mailer(mailer), gameWorld(gameWorld), username(message.username), text(message.text) {}

    void execute()
    {
        if (username == "")
        {
            Player* player = gameWorld.findPlayerByConnectionId(connectionId);
            if (player != NULL)
            {
                username = player->username;
            }
            else
            {
                return;
            }
            for (int i = 0; i < gameWorld.players.size(); i++)
            {
                mailer.push(gameWorld.players[i]->connectionId, new ChatMessage(username, text));
            }
        }
        else
        {
            //  Send message to specific user here later.
        }
    }
};
