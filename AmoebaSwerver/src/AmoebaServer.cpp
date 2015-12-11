#include "GameLib.hpp"

int main(int argc, char *argv[])
{
    int maxConnections = argc > 1 ? toInt(argv[1]) : 10;
    int port = argc > 2 ? toInt(argv[2]) : 8080;
    cout << "Maximum allowed connections: " << maxConnections << endl;
    cout << "Working on port: " << port << endl;

    NetworkController& networkController = *new AmoebaNetworkServerController(maxConnections, port);
    networkController.start();
    networkController.sender.threadInterval = 5;

    //  Application/Game specific stuff
    DefaultPhysicsEngine physicsEngine(0.5);
    GameWorld gameWorld(physicsEngine);
    GameThread game(gameWorld, networkController.incomingMailer, networkController.outgoingMailer, networkController.connectionPool);
    game.run(Thread::infiniteLoop, 20);
}
