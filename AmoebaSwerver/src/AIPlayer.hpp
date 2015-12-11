class AIPlayer : public PhysicalObject
{
public:
    Player player;
    Blob& blob;

    AIPlayer() : PhysicalObject("AIPlayer"), player(Player(9001, 9001, "AI Player")), blob(player.blob)
    {
        blob.resistance = -DefaultPhysicsEngine::resistance;
        tangible = ghostLike;
        changeColor();
        width = Blob::maxSize * 0.8;
        length = width;
    }

    void onStep()
    {
        setCenterPoint(blob.getCenterPoint());
        if (blob.currentSize > Blob::maxSize)
        {
            blob.reset();
            changeColor();
        }
        int chance;
        if (collisions.size() == 1)
        {
            chance = random(10, 1);
        }
        else
        {
            chance = random(3, 1);
        }
        if (chance == 1)
        {
            int direction = random(360);
            blob.move(direction);
        }
    }

    void onCollision(PhysicalObject& that)
    {
        double dir;
        if (&that == &blob)
        {
            return;
        }
        if (that.width < blob.currentSize)
        {
            degreeAngleBetweenPoints(blob.getCenterPoint(), that.getCenterPoint(), dir);
            blob.move(dir);
        }
        else
        {
            degreeAngleBetweenPoints(blob.getCenterPoint(), that.getCenterPoint(), dir);
            dir = 360 - dir;
            blob.move(dir);
        }
    }

private:

    void changeColor()
    {
        switch(random(5, 0))
        {
        case 0:
            blob.color = "red";
            break;
        case 1:
            blob.color = "blue";
            break;
        case 2:
            blob.color = "green";
            break;
        case 3:
            blob.color = "purple";
            break;
        case 4:
            blob.color = "orange";
            break;
        case 5:
            blob.color = "white";
            break;
        };
    }
};
