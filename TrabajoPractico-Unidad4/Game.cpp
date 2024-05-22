#include "Game.h"
#include "Box2DHelper.h"
#include <iostream>

//constructor que define ventana, frames, la escala e inicia físicas
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

//el clásico gameloop
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

//actualiza el phyworld
void Game::Actualizar()
{
	phyWorld->Step(frameTime, 8, 8);
	phyWorld->ClearForces();
	phyWorld->DebugDraw();

}
//para dibujar objetos, no se usa pero lo dejamos para cuando hagamos el final con los sprites
void Game::Dibujar()
{
	

}

void Game::Eventos()
{

	//fijar la posición del cañon
	b2Vec2 cannonPosition(6.0f, 93.0f);

	//sacar la posición del cursor del mouse y pasarla a la escala de box2d
	sf::Vector2i mousePosition = sf::Mouse::getPosition(*wnd);
	sf::Vector2f worldMousePosition = wnd->mapPixelToCoords(mousePosition);
	b2Vec2 mouseWorldPosition(mousePosition.x * scaleX, mousePosition.y * scaleY);

	//establecer la distancia entre el cursor y el cañon
	b2Vec2 displacement = mouseWorldPosition - cannonPosition;
	//obtener el ángulo del vector
	float angle = atan2(displacement.y, displacement.x);


	// Calcular la distancia entre el cañon y el cursor
	float distance = sqrt(displacement.x * displacement.x + displacement.y * displacement.y);
	//crear la potencia del cañon en base a la distancia del cursor
	float fuerza = distance * 15;



	//pasar el angulo a grados - por si fuera necesario más adelante//
	float angleInDegrees = angle * 180.0f / b2_pi;


	//el cañon rota al ángulo en que se encuentra el cursor
	cannon->SetTransform(b2Vec2(6.0f, 93.0f), angle);

	//la mitad aproximada de la longitud del cañon para obtener la punta
	float cannonLargo = 5.5f;

	//obtener la posición de la punta del cañon ajustandola al angulo de rotación
	b2Vec2 cannonTipPosition(
		cannonPosition.x + cannonLargo * cos(angle),
		cannonPosition.y + cannonLargo * sin(angle)
	);

	Event evt;
	while (wnd->pollEvent(evt))
	{
		switch (evt.type)
		{
		case Event::Closed:
			wnd->close();
			break;
		case Event::MouseButtonPressed:
			if (ragdolls.size() >= 5) {
				// Eliminar el primer ragdoll si ya hay 5 ragdolls
				delete ragdolls.front();
				ragdolls.pop_front();
			}
			//crear el ragdoll en la punta del cañon
			Ragdoll* ragdoll = new Ragdoll(phyWorld, cannonTipPosition);
			//aplicar el impulso basado en la fuerza que está afectada por la distancia del cursor y el ángulo
			b2Vec2 impulse(fuerza * cos(angleInDegrees * b2_pi / 180.0f), fuerza * sin(angleInDegrees * b2_pi / 180.0f));
			//se aplica el impulso
			ragdoll->applyImpulse(impulse);
			ragdolls.push_back(ragdoll);
			break;
					

		}
	}



}

//fijamos la escala
void Game::SetZoom()
{
	View camera;
	camera.setSize(100.0f, 100.0f);
	camera.setCenter(50.0f, 50.0f);
	wnd->setView(camera);

	//obtenemos la escala para usarla con el cursor
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

	//creamos dos obstáculos estáticos
	b2Body* obstaculo1 = Box2DHelper::CreateRectangularStaticBody(phyWorld, 20, 5);
	obstaculo1->SetTransform(b2Vec2(60.0f, 60.0f), 0.0f);

	b2Body* obstaculo2 = Box2DHelper::CreateRectangularStaticBody(phyWorld, 20, 10);
	obstaculo2->SetTransform(b2Vec2(80.0f, 80.0f), 0.0f);

	//creamos dos obstàculos dinámicos
	b2Body* obstaculo3 = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 5, 10, 0.1f, 0.1f, 0.1f);
	obstaculo3->SetTransform(b2Vec2(80.0f, 70.0f), 0.0f);

	b2Body* obstaculo4 = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 5, 10, 0.1f, 0.1f, 0.1f);
	obstaculo4->SetTransform(b2Vec2(55.0f, 53.0f), 0.0f);


	//creamos la base del cañon
	b2Body* cannon_base = Box2DHelper::CreateCircularStaticBody(phyWorld, 2);
	cannon_base->SetTransform(b2Vec2(6.0f, 93.0f), 0.0f);

	//creamos el cañon
	cannon = Box2DHelper::CreateRectangularStaticBody(phyWorld, 11, 1.2f);



}

//destructor de game
Game::~Game(void) {
	for (auto& ragdoll : ragdolls) {
		delete ragdoll;
	}
	delete phyWorld;
	delete debugRender;
}