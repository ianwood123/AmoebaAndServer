class GameWorld
{
public:
    PhysicsEngine& physicsEngine;
    deque<Player*> players;
    Pellet pellets[500];
    AIPlayer ais[5];

    GameWorld(PhysicsEngine& physicsEngine) : physicsEngine(physicsEngine) {}

    void addPlayer(int connectionId, long playerId, string username)
    {
        players.push_back(new Player(connectionId, playerId, username));
    }

    void removePlayer(Player& player)
    {
        for (int i = 0; i < players.size(); i++)
        {
            if (players[i] == &player)
            {
                delete &player;
                players.erase(players.begin() + i);
            }
        }
    }

    void removePlayerByPlayerId(long playerId)
    {
        for (int i = 0; i < players.size(); i++)
        {
            if (players[i]->playerId == playerId)
            {
                removePlayer(*players[i]);
            }
        }
    }

    void removePlayerByConnectionId(int connectionId)
    {
        for (int i = 0; i < players.size(); i++)
        {
            if (players[i]->connectionId == connectionId)
            {
                removePlayer(*players[i]);
            }
        }
    }

    Player* findPlayerByPlayerId(long playerId)
    {
        for (int i = 0; i < players.size(); i++)
        {
            if (players[i]->playerId == playerId)
            {
                return players[i];
            }
        }
        return NULL;
    }

    Player* findPlayerByConnectionId(int connectionId)
    {
        for (int i = 0; i < players.size(); i++)
        {
            if (players[i]->connectionId == connectionId)
            {
                return players[i];
            }
        }
        return NULL;
    }

    deque<PhysicalObject*> getVisibleObjects(ViewWindow window)
    {
        deque<PhysicalObject*> visibleObjects;
        deque<PhysicalObject*> objects = PhysicalObject::getObjects();

        for (int i = 0; i < objects.size(); i++)
        {
            if (window.inView(objects[i]))
            {
                visibleObjects.push_back(objects[i]);
            }
        }
        return visibleObjects;
    }

    void update()
    {
        physicsEngine.update(PhysicalObject::getObjects());
    }
};
