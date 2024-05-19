#include "Game.h"
#include "Box2DHelper.h"
#include <iostream>

Game::Game(int ancho, int alto, std::string titulo)
{
	wnd = new RenderWindow(VideoMode(ancho, alto), titulo);
	wnd->setVisible(true);
	fps = 60;
	wnd->setFramerateLimit(fps);
	frameTime = 1.0f / fps;
	SetZoom();
	InitPhysics();


}

void Game::loop()
{
	while (wnd->isOpen())
	{
		wnd->clear(clearColor);
		Eventos();
		Actualizar();
		Dibujar();
		wnd->display();

	}
}

void Game::Actualizar()
{
	phyWorld->Step(frameTime, 8, 8);
	phyWorld->ClearForces();
	phyWorld->DebugDraw();

}

void Game::Dibujar()
{
	//acà iría dibujar y actualizar el avatar

}

void Game::Eventos()
{
	Event evt;
	while (wnd->pollEvent(evt))
	{
		switch (evt.type)
		{
		case Event::Closed:
			wnd->close();
			break;
		

		}
	}
	b2Vec2 cannonPosition(6.0f, 93.0f);




	sf::Vector2i mousePosition = sf::Mouse::getPosition(*wnd);
	sf::Vector2f worldMousePosition = wnd->mapPixelToCoords(mousePosition);
	b2Vec2 mouseWorldPosition(mousePosition.x * scaleX, mousePosition.y * scaleY);

	b2Vec2 displacement = mouseWorldPosition - cannonPosition;
	float angle = atan2(displacement.y, displacement.x);

	float angleInDegrees = angle * 180.0f / b2_pi;

	/// FALTA AVERIGUAR LA DISTANCIA ENTRE EL CURSOR Y EL CAÑON PARA APLICAR LA POTENCIA DEL DISPARO//

	cannon->SetTransform(b2Vec2(6.0f, 93.0f), angle);
	//
	
}

void Game::SetZoom()
{
	View camera;
	camera.setSize(100.0f, 100.0f);
	camera.setCenter(50.0f, 50.0f);
	wnd->setView(camera);
	

	sf::Vector2f viewSize = camera.getSize();
	sf::Vector2u windowSize = wnd->getSize();
	scaleX = viewSize.x / windowSize.x;
	scaleY = viewSize.y / windowSize.y;
}

void Game::InitPhysics()
{
	//inicializamos el mundo
	phyWorld = new b2World(b2Vec2(0.0f, 9.8f));

	//Crear el render y setear banderas
	debugRender = new SFMLRenderer(wnd);
	debugRender->SetFlags(UINT_MAX);
	phyWorld->SetDebugDraw(debugRender);

	//creamos un piso paredes y techo
	b2Body* piso = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
	piso->SetTransform(b2Vec2(50.0f, 100.0f), 0.0f);

	b2Body* paredI = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
	paredI->SetTransform(b2Vec2(00.0f, 50.0f), 0.0f);

	b2Body* paredD = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 100);
	paredD->SetTransform(b2Vec2(100.0f, 50.0f), 0.0f);

	b2Body* techo = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
	techo->SetTransform(b2Vec2(50.0f, 0.0f), 0.0f);


	b2Body* cannon_base = Box2DHelper::CreateCircularStaticBody(phyWorld, 2);
	cannon_base->SetTransform(b2Vec2(6.0f, 93.0f), 0.0f);

	float anguloEnRadianes = -45.0f * (b2_pi / 180.0f);

	cannon = Box2DHelper::CreateRectangularStaticBody(phyWorld, 11, 1.2f);
	//cannon->SetTransform(b2Vec2(6.0f, 93.0f), anguloEnRadianes);


}

Game::~Game(void)
{ }