class ConnectorThread : public Thread
{
private:
    int port;

public:
    ConnectionPool& connectionPool;
    NetworkMessageMailer& mailer;

    ConnectorThread(ConnectionPool &connectionPool, NetworkMessageMailer &mailer, int port)
        : connectionPool(connectionPool), mailer(mailer), port(port) {}

    bool start(int repetitions = 1, int threadInterval = 1, ThreadTiming timing = milliSeconds)
    {
        Thread::start(repetitions, threadInterval, timing);
        sleep(10);  //  This is weird.  Without this delay after this thread start it crashes.
        /* Note: Track down race condition later. */
        return isRunning();
    }

    void task()
    {
        for (int i = 0; i < connectionPool.size(); i++)
        {
            Connection& connection = connectionPool.getConnection(i);
            if (connection.isConnected())
            {
                continue;
            }
            connection.accept(port);
            mailer.push(i, new NewConnectionMessage(connection.getIpAddress(), port));
        }
    }
};
