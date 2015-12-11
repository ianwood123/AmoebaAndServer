class ViewWindow
{
public:
    long x, y, z;
    int width, length, height;

    ViewWindow()
    {
        x = 0;
        y = 0;
        z = 0;
        width = 800;
        length = 600;
        height = 2;
    }

    string type() {
        return "ViewWindow";
    }

    void centerWindow(long x, long y)
    {
        this->x = x;
        this->y = y;
    }

    void centerWindow(long x, long y, long z)
    {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    void setWindowSize(int width, int length)
    {
        this->width = width;
        this->length = length;
    }

    void setWindowSize(int width, int length, int height)
    {
        this->width = width;
        this->length = length;
        this->height = height;
    }

    bool inView(PhysicalObject *object)
    {
        long OLeft = object->x - object->width/2;
        long ORight = object->x + object->width/2;
        long OFront = object->y + object->length/2;
        long OBack = object->y - object->length/2;
        long OTop = object->z + object->height/2;
        long OBottom = object->z - object->height/2;
        long WLeft = x - width/2;
        long WRight = x + width/2;
        long WFront = y + length/2;
        long WBack = y - length/2;
        long WTop = z + height/2;
        long WBottom = z - height/2;

        if (OLeft < WRight && ORight > WLeft)
        {
            if (OBack < WFront && OFront > WBack)
            {
                if (OBottom < WTop && OTop > WBottom)
                {
                    return true;
                }
            }
        }
        return false;
    }

    Point serverToClientView(Point p)
    {
        return Point((width / 2) + (p.x - x), (length / 2) + (y - p.y));
    }
};
