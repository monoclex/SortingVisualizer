#include <SFML/Graphics.hpp>
#include <SortingVisualizer/Bar.hpp>
#include <SortingVisualizer/Display.hpp>

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;

	sf::RenderWindow window(sf::VideoMode(800, 600), "OpenGL", sf::Style::Default, settings);

	auto display = Display(window, 10, 10);
	for (auto value = 1; auto &i : display.bars)
	{
		i = value;
		++value;
	}

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) window.close();
			if (event.type == sf::Event::Resized)
			{
				// SFML views are useful in games, but for me, i'd prefer if i was dealing with everything
				// as if it were regular window coordinates
				window.setView(sf::View(sf::FloatRect(0.0f, 0.0f, event.size.width, event.size.height)));
			}
		}

		window.clear();
		display.draw();

		// end the current frame
		window.display();
	}

	return 0;
}
