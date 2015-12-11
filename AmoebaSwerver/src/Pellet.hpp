class Pellet : public PhysicalObject
{
public:

    Pellet() : PhysicalObject("Pellet")
    {
        setSize(1, 1);
        updateable = false;
        reset();
    }

    void reset()
    {
        x = random(worldSize/3, -worldSize/3);
        y = random(worldSize/3, -worldSize/3);
    }
};
