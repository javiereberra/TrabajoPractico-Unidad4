#include "Ragdoll.h"

using namespace sf;


Ragdoll::Ragdoll(b2Vec2 posicion, b2World *phyWorld)
{


	torso = Box2DHelper::CreateRectangularStaticBody(phyWorld, 11, 1.2f);


}


void Ragdoll::Dibujar(RenderWindow& ventana) {
	
	

}

void Ragdoll::aplicar_fuerza(Vector2f posicion_m) {
}



Ragdoll::~Ragdoll(void)
{ }