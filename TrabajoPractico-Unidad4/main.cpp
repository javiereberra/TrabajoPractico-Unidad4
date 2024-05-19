#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "Game.h"

int main() {

	Game* Juego;
	Juego = new Game(800, 600, "Physics kit");
	Juego->loop();

	return 0;

}