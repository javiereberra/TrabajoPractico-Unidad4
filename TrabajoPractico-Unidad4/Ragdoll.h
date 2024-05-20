#pragma once
#include "Box2DHelper.h"
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>


using namespace sf;


class Ragdoll
{
private:
	


	
	b2Body* torso;

	


public:

	Ragdoll(b2Vec2 posicion, b2World *phyWorld);
	void Dibujar(RenderWindow& ventana);
	void aplicar_fuerza(Vector2f posicion_m);
	
	
	~Ragdoll(void);
	



};