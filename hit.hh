#ifndef HIT_H
#define HIT_H

#include "point3.hh"
#include "vector3.hh"

class Hit
{
public:
    // This one are public because they would need both getter and setter
    Point3 point;
    Vector3 normal;
    double scalar;


    friend std::ostream &operator<<(std::ostream &os, const Hit &hit)
    {
        os << "Hit(" << hit.point << ", " << hit.normal << ", " << hit.scalar << ")";
        return os;
    }
};

#endif