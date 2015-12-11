class DefaultPhysicsEngine : public PhysicsEngine
{
private:
    deque<PhysicalObject*> objects;
    deque<BoundingCube> cubes;

public:
    static double resistance;

    DefaultPhysicsEngine(double resistance = 1) {this->resistance = resistance;}

    void update(deque<PhysicalObject*> objects)
    {
        this->objects = objects;
        createBoundingCubes();
        for (int i = 0; i < objects.size(); i++)
        {
            PhysicalObject& object = *objects[i];
            object.onStep();
            if (!object.updateable)
            {
                continue;
            }
            applyResistance(object);
            object.momentum = object.speed * object.mass;
            Point target = calculateTargetPoint(object);
            deque<PhysicalObject*> collidingObjects = checkCollisions(object, target);
            move(object, target);
            object.collisions = collidingObjects;
            object.isColliding = false;
            for (int i = 0; i < collidingObjects.size(); i++)
            {
                object.isColliding = true;
                object.onCollision(*collidingObjects[i]);
                collidingObjects[i]->onCollision(object);
            }
        }
    }

private:

    deque<PhysicalObject*> checkCollisions(PhysicalObject& object, Point &target)
    {
        deque<PhysicalObject*> collisions;
        if (object.tangible == inTangible)
        {
            return collisions;
        }
        int index;
        for (int i = 0; i < objects.size(); i++)
        {
            if (objects[i] == &object)
            {
                index = i;
                break;
            }
        }
        for (int i = 0; i < cubes.size(); i++)
        {
            if (i != index && objects[i]->tangible != inTangible)
            {
                if (distanceBetweenPoints(target, cubes[i].center) <= cubes[index].proximity + cubes[i].proximity)
                {
                    if (object.tangible == tangible && objects[i]->tangible == tangible)
                    {
                        target = cubes[index].center;
                    }
                    collisions.push_back(objects[i]);
                }
            }
        }
        return collisions;
    }

    void createBoundingCubes()
    {
        cubes.clear();
        for (int i = 0; i < objects.size(); i++)
        {
            PhysicalObject& object = *objects[i];
            BoundingCube cube;
            if (object.tangible == inTangible)
            {
                cubes.push_back(cube);
                continue;
            }
            Point point;

            double prox = sqrt(pow(object.length, 2) + pow(object.width, 2));
            prox = sqrt(pow(prox, 2) + pow(object.height, 2));
            cube.proximity = prox / 3;

            point.x = object.x;
            point.y = object.y;
            point.z = object.z;
            cube.center = point;

//            point.x = object.x + object.width/2;
//            point.y = object.y;
//            cube.front = point;
//
//            point.x = object.x - object.width/2;
//            point.y = object.y;
//            cube.back = point;
//
//            point.x = object.x;
//            point.y = object.y + object.length/2;
//            cube.right = point;
//
//            point.x = object.x;
//            point.y = object.y - object.length/2;
//            cube.left = point;
//
//            point.x = object.x;
//            point.y = object.y;
//            point.z = object.z + object.height/2;
//            cube.top = point;
//
//            point.z = object.z - object.height/2;
//
//            cube.bottom = point;

            cubes.push_back(cube);
        }
    }

    void handleCollision(PhysicalObject& object, PhysicalObject& other)
    {
        other.momentum = other.speed * other.mass;
        object.onCollision(other);
    }

    void move(PhysicalObject& object, Point target)
    {
        object.setCenterPoint(target);
    }

    void applyResistance(PhysicalObject &object)
    {
        object.speed -= resistance + object.resistance;
        if (object.speed < 0)
        {
            object.speed = 0;
        }
    }

    Point calculateTargetPoint(PhysicalObject &object)
    {
        Point target = object.getCenterPoint();
        return calculateVector(target, object.speed, object.movingDirectionH, object.movingDirectionV);
    }
};
double DefaultPhysicsEngine::resistance;
