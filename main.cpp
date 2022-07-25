#include "SimplePendulum.h"

constexpr float WIDTH = 1000.f;
constexpr float HEIGHT = 1000.f;

int main(void)
{
	// Create a new instance
	SimplePendulum p1(WIDTH / 2, 0.f, 700.f, PI / 4, sf::Color::Blue);
	SimplePendulum p2(WIDTH / 2, 0.f, 700.f, PI / 4, sf::Color::Red);

	// Create a Window for the simulation
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Pendule simple");

	// Define deltatime
	float dt = 0.01f;

	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window: exit
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Use the update methode to compute the animation
		p1.UpdateEuler(dt);
		p2.UpdateVerlet(dt);

		window.clear();
		
		// Draw all pendulum graphic elements
		p1.Show(&window);
		p2.Show(&window);

		window.display();
	}
	return (0);
}