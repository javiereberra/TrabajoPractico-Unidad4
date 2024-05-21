#include "Ragdoll.h"
#include "Box2DHelper.h"
#include "SFMLRenderer.h"

Ragdoll::Ragdoll(b2World* world, const b2Vec2& position)
    : world(world) {
    // Crear la caja 1 (torso)
    box1 = Box2DHelper::CreateRectangularDynamicBody(world, 2.0f, 4.0f, 0.7f, 0.1, 0.1f);
    box1->SetTransform(position, 0);

    // Crear la caja 2 (cabeza) arriba de la caja 1
    b2Vec2 box2Position = position + b2Vec2(0.0f, -6.0f); // Ajustar posición para que esté encima
    box2 = Box2DHelper::CreateRectangularDynamicBody(world, 1.7f, 1.7f, 0.7f, 0.1, 0.1f);
    box2->SetTransform(box2Position, 0);

    // Crear la caja 3 (brazo derecho) al lado derecho de la caja 1
    b2Vec2 box3Position = position + b2Vec2(1.5f, 2.0f); // Ajustar posición para que esté a la derecha
    box3 = Box2DHelper::CreateRectangularDynamicBody(world, 0.7f, 2.0f, 0.7f, 0.1, 0.1f);
    box3->SetTransform(box3Position, 0);

    // Crear la caja 4 (brazo izquierdo) al lado izquierdo de la caja 1
    b2Vec2 box4Position = position + b2Vec2(-1.5f, 2.0f); // Ajustar posición para que esté a la izquierda
    box4 = Box2DHelper::CreateRectangularDynamicBody(world, 0.7f, 2.0f, 0.7f, 0.1, 0.1f);
    box4->SetTransform(box4Position, 0);

    // Crear la caja 5 (pierna derecha) debajo de la caja 1
    b2Vec2 box5Position = position + b2Vec2(0.75f, 6.0f); // Ajustar posición para que esté abajo a la derecha
    box5 = Box2DHelper::CreateRectangularDynamicBody(world, 0.7f, 3.0f, 0.7f, 0.1, 0.1f);
    box5->SetTransform(box5Position, 0);

    // Crear la caja 6 (pierna izquierda) debajo de la caja 1
    b2Vec2 box6Position = position + b2Vec2(-0.75f, 6.0f); // Ajustar posición para que esté abajo a la izquierda
    box6 = Box2DHelper::CreateRectangularDynamicBody(world, 0.7f, 3.0f, 0.7f, 0.1, 0.1f);
    box6->SetTransform(box6Position, 0);

        // Crear los joints
    b2RevoluteJointDef jointDef;

    // Unir la cabeza al torso
    jointDef.bodyA = box1;
    jointDef.bodyB = box2;
    jointDef.localAnchorA.Set(0, 2.0f); // Parte superior del torso
    jointDef.localAnchorB.Set(0, -0.7f);  // Parte inferior de la cabeza
    jointDef.collideConnected = false;
    jointHeadTorso = (b2RevoluteJoint*)world->CreateJoint(&jointDef);

    // Unir el brazo derecho al torso
    jointDef.bodyA = box1;
    jointDef.bodyB = box3;
    jointDef.enableLimit = true;
    jointDef.lowerAngle = -45 * b2_pi / 180.0f; // Ángulo mínimo de flexión en radianes
    jointDef.upperAngle = 45 * b2_pi / 180.0f; // Ángulo máximo de flexión en radianes
    jointDef.localAnchorA.Set(1.0f, 2.0f); // Lado derecho del torso
    jointDef.localAnchorB.Set(-0.35, 1.5f);   // Parte superior del brazo derecho
    jointRightArmTorso = (b2RevoluteJoint*)world->CreateJoint(&jointDef);

    // Unir el brazo izquierdo al torso
    jointDef.bodyA = box1;
    jointDef.bodyB = box4;
    jointDef.enableLimit = true;
    jointDef.lowerAngle = -45 * b2_pi / 180.0f; // Ángulo mínimo de flexión en radianes
    jointDef.upperAngle = 45 * b2_pi / 180.0f; // Ángulo máximo de flexión en radianes
    jointDef.localAnchorA.Set(-1.0f, 2.0f); // Lado izquierdo del torso
    jointDef.localAnchorB.Set(0.35f, 1.5f);     // Parte superior del brazo izquierdo
    jointLeftArmTorso = (b2RevoluteJoint*)world->CreateJoint(&jointDef);

    // Unir la pierna derecha al torso
    jointDef.bodyA = box1;
    jointDef.bodyB = box5;
    jointDef.localAnchorA.Set(0.5f, -2.0f); // Parte inferior derecha del torso
    jointDef.localAnchorB.Set(0, 1.5f);    // Parte superior de la pierna derecha
    jointRightLegTorso = (b2RevoluteJoint*)world->CreateJoint(&jointDef);

    // Unir la pierna izquierda al torso
    jointDef.bodyA = box1;
    jointDef.bodyB = box6;
    jointDef.localAnchorA.Set(-0.5f, -2.0f); // Parte inferior izquierda del torso
    jointDef.localAnchorB.Set(0, 1.5f);     // Parte superior de la pierna izquierda
    jointLeftLegTorso = (b2RevoluteJoint*)world->CreateJoint(&jointDef);
}

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

    if (box1) {
        world->DestroyBody(box1);
        box1 = nullptr;
    }
    if (box2) {
        world->DestroyBody(box2);
        box2 = nullptr;
    }
    if (box3) {
        world->DestroyBody(box3);
        box3 = nullptr;
    }
    if (box4) {
        world->DestroyBody(box4);
        box4 = nullptr;
    }
    if (box5) {
        world->DestroyBody(box5);
        box5 = nullptr;
    }
    if (box6) {
        world->DestroyBody(box6);
        box6 = nullptr;
    }
}


void Ragdoll::applyImpulse(const b2Vec2& impulse) {
    box1->ApplyLinearImpulseToCenter(impulse, true);
}

void Ragdoll::dibujar(SFMLRenderer* renderer) {
    // Dibujar la primera caja
    const b2PolygonShape* shape1 = static_cast<const b2PolygonShape*>(box1->GetFixtureList()->GetShape());
    renderer->DrawSolidPolygon(shape1->m_vertices, shape1->m_count, b2Color(1, 0, 0));

    // Dibujar la segunda caja
    const b2PolygonShape* shape2 = static_cast<const b2PolygonShape*>(box2->GetFixtureList()->GetShape());
    renderer->DrawSolidPolygon(shape2->m_vertices, shape2->m_count, b2Color(0, 1, 0));
}