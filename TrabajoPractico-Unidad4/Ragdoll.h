#pragma once
#include <Box2D/Box2D.h>
#include "SFMLRenderer.h"

class Ragdoll {
private:
    b2Body* box1;
    b2Body* box2;
    b2Body* box3;
    b2Body* box4;
    b2Body* box5;
    b2Body* box6;

    b2RevoluteJoint* jointHeadTorso;
    b2RevoluteJoint* jointRightArmTorso;
    b2RevoluteJoint* jointLeftArmTorso;
    b2RevoluteJoint* jointRightLegTorso;
    b2RevoluteJoint* jointLeftLegTorso;

    b2World* world;

public:
    
    Ragdoll(b2World* world, const b2Vec2& position);
    ~Ragdoll();

  
    void applyImpulse(const b2Vec2& impulse);
    void dibujar(SFMLRenderer* renderer);
};