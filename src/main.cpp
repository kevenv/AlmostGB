#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cartridge.h"

int main()
{
	std::cout << "AlmostGB" << std::endl;
	std::cout << "--------" << std::endl;

	Cartridge rom;
	if (!rom.load("tetris.gb")) {
		std::cout << "Couldn't load ROM" << std::endl;
	}

	std::cout << rom.toString() << std::endl;

	/*sf::RenderWindow window(sf::VideoMode(800, 600), "AlmostGB");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed || 
				sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				window.close();
			}
		}

		window.clear();
		window.display();
	}*/

	return 0;
}
