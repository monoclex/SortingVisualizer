#include <SFML/Graphics.hpp>
#include <SortingVisualizer/Algorithms/BubbleSort.hpp>
#include <SortingVisualizer/Bar.hpp>
#include <SortingVisualizer/Collection.hpp>
#include <SortingVisualizer/Display.hpp>
#include <algorithm>
#include <chrono>
#include <iostream>
#include <memory>
#include <random>
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

	auto bars = toBars(collection.contents());
	bubbleSort(collection);

	for (auto &decision : collection.getDecisions())
	{
		if (std::holds_alternative<Swap>(decision))
		{
			auto swap = std::get<Swap>(decision);

			bars[swap.leftIdx].color = sf::Color::Red;
			bars[swap.rightIdx].color = sf::Color::Red;

			std::swap(bars[swap.leftIdx], bars[swap.rightIdx]);

			display.setBars(bars);
			std::this_thread::sleep_for(std::chrono::milliseconds(16 * 2));

			bars[swap.leftIdx].color = sf::Color::White;
			bars[swap.rightIdx].color = sf::Color::White;
		}
		else if (std::holds_alternative<Comparison>(decision))
		{
			auto cmp = std::get<Comparison>(decision);

			bars[cmp.leftIdx].color = sf::Color::Cyan;
			bars[cmp.rightIdx].color = sf::Color::Cyan;

			display.setBars(bars);
			std::this_thread::sleep_for(std::chrono::milliseconds(16));

			bars[cmp.leftIdx].color = sf::Color::White;
			bars[cmp.rightIdx].color = sf::Color::White;
		}
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

	std::vector<uint64_t> values;
	auto len = 100;
	for (auto i = 1; i <= len; ++i)
	{
		values.push_back(i);
	}
	std::shuffle(values.begin(), values.end(), std::mt19937(std::random_device()()));
	auto collection = Collection(values);

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
				window.close();
				exit(0);
			}
		}

		window.clear();
		display.draw();
		window.display();
	}

	return 0;
}
