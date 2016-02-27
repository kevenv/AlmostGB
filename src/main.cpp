#include <iostream>
#include <SFML/Graphics.hpp>
#include "Cartridge.h"
#include "CPU.h"
#include "MMU.h"

int main()
{
	std::cout << "AlmostGB" << std::endl;
	std::cout << "--------" << std::endl;

	Cartridge cartridge;
	if (!cartridge.load("tetris.gb")) {
		std::cout << "Couldn't load ROM" << std::endl;
	}

	std::cout << cartridge.toString() << std::endl;

	MMU mmu;
	mmu.mapCartridge(cartridge);

	CPU cpu;
	cpu.connectMMU(mmu);
	cpu.reset();

	while (1) {

		int cyclesCurrFrame = 0;
		while (cyclesCurrFrame <= CPU::MAX_CYCLES_PER_FRAME) {
			int cycles = cpu.tick();
			cyclesCurrFrame += cycles;
		}

		//render frame
	}

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
