#include "Ragdoll.h"
#include "Box2DHelper.h"
#include "SFMLRenderer.h"

Ragdoll::Ragdoll(b2World* world, const b2Vec2& position, float boxWidth, float boxHeight)
    : world(world) {
    // Crear la primera caja
    box1 = Box2DHelper::CreateRectangularDynamicBody(world, boxWidth, boxHeight, 1.0f, 1.0f, 1.0f);
    box1->SetTransform(position, 0);

    // Crear la segunda caja
    b2Vec2 box2Position = position + b2Vec2(0.0f, boxHeight * 1.5f); // Ajustar posición para que estén cerca
    box2 = Box2DHelper::CreateRectangularDynamicBody(world, boxWidth, boxHeight, 1.0f, 1.0f, 1.0f);
    box2->SetTransform(box2Position, 0);

    // Crear el joint que une las dos cajas
    b2RevoluteJointDef jointDef;
    jointDef.bodyA = box1;
    jointDef.bodyB = box2;
    jointDef.localAnchorA.Set(0, boxHeight / 2);
    jointDef.localAnchorB.Set(0, -boxHeight / 2);
    jointDef.collideConnected = false;
    joint = (b2RevoluteJoint*)world->CreateJoint(&jointDef);
}

Ragdoll::~Ragdoll() {
    world->DestroyBody(box1);
    world->DestroyBody(box2);
    world->DestroyJoint(joint);
}

void Ragdoll::setPosition(const b2Vec2& position) {
    box1->SetTransform(position, 0);
    b2Vec2 box2Position = position + b2Vec2(0.0f, box1->GetFixtureList()->GetAABB(0).GetExtents().y * 3.0f);
    box2->SetTransform(box2Position, 0);
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