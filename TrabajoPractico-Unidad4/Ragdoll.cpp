#include "Ragdoll.h"
#include "Box2DHelper.h"
#include "SFMLRenderer.h"

//constructor de ragdoll
Ragdoll::Ragdoll(b2World* world, const b2Vec2& position)
    : world(world) {
    // Crear torso
    torso = Box2DHelper::CreateRectangularDynamicBody(world, 2.0f, 4.0f, 0.7f, 0.1, 0.1f);
    torso->SetTransform(position, 0);

    // Crear cabeza
    b2Vec2 cabezaPosition = position + b2Vec2(0.0f, -7.0f); // Ajustar posición para que esté encima
    cabeza = Box2DHelper::CreateRectangularDynamicBody(world, 1.7f, 1.7f, 0.7f, 0.1, 0.1f);
    cabeza->SetTransform(cabezaPosition, 0);

    // Crear brazo derecho
    b2Vec2 brazoDPosition = position + b2Vec2(1.5f, 2.0f); // Ajustar posición para que esté a la derecha
    brazoD = Box2DHelper::CreateRectangularDynamicBody(world, 0.7f, 2.5f, 0.7f, 0.1, 0.1f);
    brazoD->SetTransform(brazoDPosition, 0);

    // Crear brazo izquierdo
    b2Vec2 brazoIPosition = position + b2Vec2(-1.5f, 2.0f); // Ajustar posición para que esté a la izquierda
    brazoI = Box2DHelper::CreateRectangularDynamicBody(world, 0.7f, 2.5f, 0.7f, 0.1, 0.1f);
    brazoI->SetTransform(brazoIPosition, 0);

    // Crear pierna derecha
    b2Vec2 piernaDPosition = position + b2Vec2(0.75f, 6.0f); // Ajustar posición para que esté abajo a la derecha
    piernaD = Box2DHelper::CreateRectangularDynamicBody(world, 0.7f, 3.0f, 0.7f, 0.1, 0.1f);
    piernaD->SetTransform(piernaDPosition, 0);

    // Crear pierna izquierda
    b2Vec2 piernaIPosition = position + b2Vec2(-0.75f, 6.0f); // Ajustar posición para que esté abajo a la izquierda
    piernaI = Box2DHelper::CreateRectangularDynamicBody(world, 0.7f, 3.0f, 0.7f, 0.1, 0.1f);
    piernaI->SetTransform(piernaIPosition, 0);

        // Crear los joints
    b2RevoluteJointDef jointDef;

    // Unir la cabeza al torso
    jointDef.bodyA = torso;
    jointDef.bodyB = cabeza;
    jointDef.localAnchorA.Set(0, 2.0f); // Parte superior del torso
    jointDef.localAnchorB.Set(0, -0.7f);  // Parte inferior de la cabeza
    jointDef.collideConnected = false;
    jointHeadTorso = (b2RevoluteJoint*)world->CreateJoint(&jointDef);

    // Unir el brazo derecho al torso
    jointDef.bodyA = torso;
    jointDef.bodyB = brazoD;
    jointDef.enableLimit = true;
    jointDef.lowerAngle = -45 * b2_pi / 180.0f; // Ángulo mínimo de flexión en radianes
    jointDef.upperAngle = 45 * b2_pi / 180.0f; // Ángulo máximo de flexión en radianes
    jointDef.localAnchorA.Set(1.0f, 2.0f); // Lado derecho del torso
    jointDef.localAnchorB.Set(-0.35, 1.5f);   // Parte superior del brazo derecho
    jointRightArmTorso = (b2RevoluteJoint*)world->CreateJoint(&jointDef);

    // Unir el brazo izquierdo al torso
    jointDef.bodyA = torso;
    jointDef.bodyB = brazoI;
    jointDef.enableLimit = true;
    jointDef.lowerAngle = -45 * b2_pi / 180.0f; // Ángulo mínimo de flexión en radianes
    jointDef.upperAngle = 45 * b2_pi / 180.0f; // Ángulo máximo de flexión en radianes
    jointDef.localAnchorA.Set(-1.0f, 2.0f); // Lado izquierdo del torso
    jointDef.localAnchorB.Set(0.35f, 1.5f);     // Parte superior del brazo izquierdo
    jointLeftArmTorso = (b2RevoluteJoint*)world->CreateJoint(&jointDef);

    // Unir la pierna derecha al torso
    jointDef.bodyA = torso;
    jointDef.bodyB = piernaD;
    jointDef.localAnchorA.Set(0.5f, -2.0f); // Parte inferior derecha del torso
    jointDef.localAnchorB.Set(0, 1.5f);    // Parte superior de la pierna derecha
    jointRightLegTorso = (b2RevoluteJoint*)world->CreateJoint(&jointDef);

    // Unir la pierna izquierda al torso
    jointDef.bodyA = torso;
    jointDef.bodyB = piernaI;
    jointDef.localAnchorA.Set(-0.5f, -2.0f); // Parte inferior izquierda del torso
    jointDef.localAnchorB.Set(0, 1.5f);     // Parte superior de la pierna izquierda
    jointLeftLegTorso = (b2RevoluteJoint*)world->CreateJoint(&jointDef);
}

//destructor

Ragdoll::~Ragdoll() {
    if (jointHeadTorso) {
        world->DestroyJoint(jointHeadTorso);
        jointHeadTorso = nullptr;
    }
    if (jointRightArmTorso) {
        world->DestroyJoint(jointRightArmTorso);
        jointRightArmTorso = nullptr;
    }
    if (jointLeftArmTorso) {
        world->DestroyJoint(jointLeftArmTorso);
        jointLeftArmTorso = nullptr;
    }
    if (jointRightLegTorso) {
        world->DestroyJoint(jointRightLegTorso);
        jointRightLegTorso = nullptr;
    }
    if (jointLeftLegTorso) {
        world->DestroyJoint(jointLeftLegTorso);
        jointLeftLegTorso = nullptr;
    }

    if (torso) {
        world->DestroyBody(torso);
        torso = nullptr;
    }
    if (cabeza) {
        world->DestroyBody(cabeza);
        cabeza = nullptr;
    }
    if (brazoD) {
        world->DestroyBody(brazoD);
        brazoD = nullptr;
    }
    if (brazoI) {
        world->DestroyBody(brazoI);
        brazoI = nullptr;
    }
    if (piernaD) {
        world->DestroyBody(piernaD);
        piernaD = nullptr;
    }
    if (piernaI) {
        world->DestroyBody(piernaI);
        piernaI = nullptr;
    }
}

//para aplicarle la fuerza del cañon

void Ragdoll::applyImpulse(const b2Vec2& impulse) {
    torso->ApplyLinearImpulseToCenter(impulse, true);
}

