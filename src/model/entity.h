#ifndef SERVER_ENTITY_H
#define SERVER_ENTITY_H

#include "src/utils/objectid.h"
#include <memory>

struct Position {
    float x;
    float y;
};

class Entity {
public:
    Entity();
    virtual ~Entity();
    objectID getObjectID() const;
    void setPositionX(int x);
    void setPositionY(int y);
    void setPosition(Position p);
    void setPostiion(int x, int y);
    Position getPosition() const;
    float getPositionX() const;
    float getPositionY() const;

protected:
    objectID _id;
    Position pos;
};


#endif //SERVER_ENTITY_H
