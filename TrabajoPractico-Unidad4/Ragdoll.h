#pragma once
#include <Box2D/Box2D.h>
#include "SFMLRenderer.h"

class Ragdoll {
private:
    b2Body* box1;
    b2Body* box2;
    b2RevoluteJoint* joint;
    b2World* world;

public:
    Ragdoll(b2World* world, const b2Vec2& position, float boxWidth, float boxHeight);
    ~Ragdoll();

    void setPosition(const b2Vec2& position);
    void applyImpulse(const b2Vec2& impulse);
    void dibujar(SFMLRenderer* renderer);
};