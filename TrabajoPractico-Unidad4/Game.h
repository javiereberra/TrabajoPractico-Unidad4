#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"
#include "Ragdoll.h"
#include <list>

using namespace sf;

class Game
{
private:
	//propiedades de ventana
	int alto;
	int ancho;
	RenderWindow* wnd;
	Color clearColor;

	//objeto de Box2d
	b2World* phyWorld;
	SFMLRenderer* debugRender;

	//tiempo de frame
	float frameTime;
	int fps;


	//cuerpo del cañon

	b2Body* cannon;

	//variables para medir la escala
	float scaleX;
	float scaleY;


	std::list<Ragdoll*> ragdolls;

public:

	Game(int ancho, int alto, std::string titulo);
	~Game(void);
	void InitPhysics();

	//main gameloop

	void loop();
	void Dibujar();
	void Actualizar();
	void Eventos();
	void SetZoom();



};