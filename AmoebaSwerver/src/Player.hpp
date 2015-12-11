class Player
{
public:
    long playerId;
    int connectionId;
    string username;
    ViewWindow window;
    Blob blob;

    Player(int connectionId, long playerId, string username)
        : connectionId(connectionId), playerId(playerId), username(username), blob(Blob(this)) {}
};
