class GameThread : public Thread
{
private:
    CommandFactory commandFactory;
    GameWorldPoller poller;
    ConnectionPool& connectionPool;
    NetworkMessageMailer &incomingMailer;
    NetworkMessageMailer &outgoingMailer;
    GameWorld& gameWorld;

public:

    GameThread(GameWorld& gameWorld, NetworkMessageMailer& incomingMailer, NetworkMessageMailer& outgoingMailer, ConnectionPool& connectionPool)
    :   gameWorld(gameWorld), incomingMailer(incomingMailer), outgoingMailer(outgoingMailer), connectionPool(connectionPool),
        commandFactory(CommandFactory(gameWorld, connectionPool, outgoingMailer)), poller(GameWorldPoller(gameWorld)) {}

    void setUp()
    {
        CheckLoginThread::instantiate(gameWorld, connectionPool, outgoingMailer);
    }

    void task()
    {
        deque<NetworkMessage*> incomingMessages = incomingMailer.dump();
        deque<Command*> commands = commandFactory.generateCommands(incomingMessages);
        executeCommands(commands);
        gameWorld.update();
        if (outgoingMailer.messageCount() == 0)
        {
            deque<NetworkMessage*> outgoingMessages = poller.poll();
            outgoingMailer.push(outgoingMessages);
        }
    }

private:

    void executeCommands(deque<Command*> commands)
    {
        for (int i = 0; i < commands.size(); i++)
        {
            commands[i]->execute();
            delete commands[i];
        }
    }
};
