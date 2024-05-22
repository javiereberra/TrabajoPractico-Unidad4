#pragma once
#include <Box2D/Box2D.h>
#include "SFMLRenderer.h"

class Ragdoll {
private:
    //las partes del ragdoll
    b2Body* torso;
    b2Body* cabeza;
    b2Body* brazoD;
    b2Body* brazoI;
    b2Body* piernaD;
    b2Body* piernaI;

    //los joints que unen a todas las partes
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
    
};