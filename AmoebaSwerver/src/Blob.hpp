class Blob : public PhysicalObject
{
public:
    Player& player;
    string color;
    double currentSpeed;
    double currentSize;
    static const double maxSpeed = 10;
    static const double maxSize = 500;

    Blob(Player* player, string color = "black") : PhysicalObject("Blob"), player(*player), color(color)
    {
        reset();
    }

    void onStep()
    {
        x = wrapToScreen(x, worldSize/2, -worldSize/2);
        y = wrapToScreen(y, worldSize/2, -worldSize/2);
        setSize(currentSize, currentSize);
    }

    void move(double direction)
    {
        setFacingDirection(direction);
        setVelocity(currentSpeed, direction);
    }

    void reset()
    {
        currentSpeed = maxSpeed;
        currentSize = 10;
        x = random(worldSize/2, -worldSize/2);
        y = random(worldSize/2, -worldSize/2);
        setVelocity(0, 0);
    }

    void onCollision(PhysicalObject& that)
    {
        if (that.type == "AIPlayer"){return;}
        if ( currentSize > that.width && currentSize < maxSize)
        {
            currentSize += that.width;
            currentSpeed = currentSpeed > 4 ? maxSpeed - sqrt(maxSpeed * maxSpeed * (currentSize / maxSize)) : 4;
            that.reset();
        }
        else if (currentSize >= maxSize)
        {
            reset();
        }
    }
};
