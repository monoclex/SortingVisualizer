#include <SFML/Graphics.hpp>
#include <SortingVisualizer/Algorithms/BubbleSort.hpp>
#include <SortingVisualizer/Collection.hpp>
#include <SortingVisualizer/Display.hpp>
#include <iostream>

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 16;

	sf::RenderWindow window(sf::VideoMode(800, 600), "Sorting Visualizer", sf::Style::Default, settings);
	window.setActive(false);
	window.setVerticalSyncEnabled(true);

	Collection collection(10);
	Display display(window, collection);

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

		collection.randomize();
		display.draw();

		window.display();
	}

	return 0;
}
