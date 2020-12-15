#include <Bar.hpp>
#include <SFML/Graphics.hpp>

int main()
{
	// create the window (remember: it's safer to create it in the main thread due to OS limitations)
	sf::RenderWindow window(sf::VideoMode(800, 600), "OpenGL");

	// activate its OpenGL context
	window.setActive(true);

	auto size = sf::Vector2f(window.getSize());

	// the event/logic/whatever loop
	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed) window.close();
		}

		// draw...
		window.clear(sf::Color::Green);

		sf::RectangleShape bar(sf::Vector2f(0.0f, 0.0f));
		bar.setSize(size);
		bar.setFillColor(sf::Color::Black);
		size.x -= 0.01f;
		size.y -= 0.01f;
		window.draw(bar);

		// end the current frame
		window.display();
	}

	return 0;
}
