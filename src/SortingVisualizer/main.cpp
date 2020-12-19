#include <SFML/Graphics.hpp>
#include <SortingVisualizer/Algorithms/BubbleSort.hpp>
#include <SortingVisualizer/Collection.hpp>
#include <SortingVisualizer/Display.hpp>
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <tuple>

void sorter(std::tuple<Collection *, Display *> container)
{
	auto collectionPtr = std::get<0>(container);
	auto displayPtr = std::get<1>(container);

	if (collectionPtr == nullptr) throw "didn't expect nullptr for collection";
	if (displayPtr == nullptr) throw "didn't expect nullptr for display";

	auto collection = *collectionPtr;
	auto display = *displayPtr;

	auto bars = collection.contents();
	bubbleSort(collection);

	for (auto &decision : collection.getDecisions())
	{
		if (std::holds_alternative<Swap>(decision))
		{
			auto swap = std::get<Swap>(decision);
			std::swap(bars[swap.leftIdx], bars[swap.rightIdx]);
			display.setBars(bars);
		}

		std::this_thread::sleep_for(std::chrono::milliseconds(16));
	}
}

int main()
{
	// seed RNG
	std::srand(std::time(0));

	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;

	auto window = sf::RenderWindow(sf::VideoMode(800, 600), "Sorting Visualizer", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(60);

	auto collection = Collection(100);
	collection.randomize();

	auto display = Display(window, collection);

	auto dirty = true;

	sf::Thread sortAlgo(&sorter, std::make_tuple<Collection *, Display *>(&collection, &display));
	sortAlgo.launch();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Resized)
			{
				[[likely]]
				// SFML views are useful in games, but for me, i'd prefer if i was dealing with everything
				// as if it were regular window coordinates
				window.setView(sf::View(sf::FloatRect(0.0f, 0.0f, event.size.width, event.size.height)));

				// we modified the view, we want to guarantee a re-render
				dirty = true;
			}
			else if (event.type == sf::Event::LostFocus)
			{
				window.setFramerateLimit(12);
			}
			else if (event.type == sf::Event::GainedFocus)
			{
				window.setFramerateLimit(60);
			}
			else if (event.type == sf::Event::Closed)
			{
				[[unlikely]] window.close();
				exit(0);
			}
		}

		window.clear();
		display.draw();
		window.display();
	}

	return 0;
}
