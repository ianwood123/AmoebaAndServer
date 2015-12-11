class GameWorldPoller
{
private:
    GameWorld &gameWorld;

public:
    GameWorldPoller(GameWorld& gameWorld) : gameWorld(gameWorld) {}

    deque<NetworkMessage*> poll()
    {
        deque<NetworkMessage*> messages;
        deque<Player*> players = gameWorld.players;
        for (int i = 0; i < players.size(); i++)
        {
            ViewWindow window = players[i]->window;
            deque<PhysicalObject*> objects = gameWorld.getVisibleObjects(window);
            deque<NetworkMessage*> playerMessages = deconstructObjects(window, objects);
            setConnectionIds(players[i]->connectionId, playerMessages);
            messages.insert(messages.end(), playerMessages.begin(), playerMessages.end());
        }
        return messages;
    }

private:

    void setConnectionIds(int connectionId, deque<NetworkMessage*> playerMessages)
    {
        for (int i = 0; i < playerMessages.size(); i++)
        {
            playerMessages[i]->connectionId = connectionId;
        }
    }

    deque<NetworkMessage*> deconstructObjects(ViewWindow window, deque<PhysicalObject*> objects)
    {
        deque<NetworkMessage*> messages;
        for (int i = 0; i < objects.size(); i++)
        {
            PhysicalObject& o = *objects[i];
            string objectType = o.type;
            if (objectType == "Blob")
            {
                Blob& blob = (Blob&)o;
                deque<KeyValuePair> properties;
                Point p = window.serverToClientView(blob.getCenterPoint());
                properties.push_back(KeyValuePair("x", toString(p.x)));
                properties.push_back(KeyValuePair("y", toString(p.y)));
                properties.push_back(KeyValuePair("size", toString(blob.width)));
                properties.push_back(KeyValuePair("color", blob.color));
                properties.push_back(KeyValuePair("username", blob.player.username));
                properties.push_back(KeyValuePair("id",toString(blob.objectId)));
                messages.push_back(new BlobStateMessage(properties));
            }
            else if (objectType == "Pellet")
            {
                Pellet& pellet = (Pellet&)o;
                Point p = window.serverToClientView(pellet.getCenterPoint());
                int x = (p.x);
                int y = (p.y);
                messages.push_back(new PelletPositionMessage(x, y, pellet.objectId));
            }
        }
        return messages;
    }
};
