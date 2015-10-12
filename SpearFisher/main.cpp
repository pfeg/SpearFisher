#include <SFML/Graphics.hpp>
#include "ParticleSystem.h"




/*********************************************


TEST POST PLEASE IGNORE


*********************************************/




int main()
{
	// create the window
	sf::RenderWindow window(sf::VideoMode(1000, 700), "Particles");

	// create the particle system
	ParticleSystem particles(10000);

	// create a clock to track the elapsed time
	sf::Clock clock;
	sf::Vector2i prevMouse = sf::Vector2i(0, 0);

	// run the main loop
	while (window.isOpen())
	{
		// handle events
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// make the particle system emitter follow the mouse
		sf::Vector2i mouse = sf::Mouse::getPosition(window);
		sf::Vector2f vel = (sf::Vector2f)(mouse - prevMouse);
		//vel = sf::Vector2f(vel.x / clock.getElapsedTime().asSeconds(), vel.y / clock.getElapsedTime().asSeconds());
		particles.setEmitter(window.mapPixelToCoords(mouse), vel);
		prevMouse = mouse;
		
		// update it
		sf::Time elapsed = clock.restart();
		particles.update(elapsed);

		// draw it
		window.clear();
		window.draw(particles);
		window.display();
	}

	return 0;
}