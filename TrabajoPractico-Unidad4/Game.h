#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"
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

	
	//// ACÁ IRÍAN LOS CUERPOS AVATAR Y JOINTS
	b2Body* cannon; 

	float scaleX;
	float scaleY;


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