#include <SFML/Graphics.hpp>
#include <SortingVisualizer/Algorithms/QuickSort.hpp>
#include <SortingVisualizer/Bar.hpp>
#include <SortingVisualizer/Collection.hpp>
#include <SortingVisualizer/Display.hpp>
#include <algorithm>
#include <chrono>
#include <memory>
#include <random>
#include <stdexcept>
#include <thread>
#include <tuple>

////////////////////
// TODO: CLEAN UP //
////////////////////
//
// see, the joke is that i call it a "TODO" but don't plan to ever do it
// as a sidenote i made comments every so often so it's obvious what should be put into a function if i ever decide to not feel lazy
// (narrator: he never did)

// helper method for sorter below
void handleSingleDecision(SingleDecision &decision, std::vector<Bar> &bars, std::vector<std::size_t> &coloredBars)
{
	if (std::holds_alternative<Swap>(decision))
	{
		auto swap = std::get<Swap>(decision);
		bars[swap.leftIdx].color = bars[swap.rightIdx].color = sf::Color::Red;
		coloredBars.push_back(swap.leftIdx);
		coloredBars.push_back(swap.rightIdx);

		std::swap(bars[swap.leftIdx], bars[swap.rightIdx]);
	}
	else if (std::holds_alternative<Comparison>(decision))
	{
		auto cmp = std::get<Comparison>(decision);
		bars[cmp.leftIdx].color = bars[cmp.rightIdx].color = sf::Color::Cyan;
		coloredBars.push_back(cmp.leftIdx);
		coloredBars.push_back(cmp.rightIdx);
	}
	else
	{
		throw std::logic_error("couldn't match on variant");
	}
}

// worker on a separate thread that will update the display's bars
void sorter(std::tuple<Collection *, Display *> container)
{
	// boiler plate of container -> collection & display
	auto collectionPtr = std::get<0>(container);
	auto displayPtr = std::get<1>(container);

	if (collectionPtr == nullptr) throw "didn't expect nullptr for collection";
	if (displayPtr == nullptr) throw "didn't expect nullptr for display";

	auto collection = *collectionPtr;
	auto display = *displayPtr;

	// sort the collection
	auto bars = toBars(collection.contents());
	quickSort(collection);

	// display the sorting
	for (auto &decision : collection.getDecisions(1000))
	{
		std::vector<std::size_t> coloredBars;

		// change colors of bars, and add them to coloredBars to change them back later
		if (std::holds_alternative<std::vector<SingleDecision>>(decision))
		{
			auto decisions = std::get<std::vector<SingleDecision>>(decision);

			for (auto &d : decisions)
			{
				handleSingleDecision(d, bars, coloredBars);
			}
		}
		else if (std::holds_alternative<SingleDecision>(decision))
		{
			auto d = std::get<SingleDecision>(decision);
			handleSingleDecision(d, bars, coloredBars);
		}
		else
		{
			throw std::logic_error("couldn't match on variant");
		}

		display.setBars(bars);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));

		for (auto &idx : coloredBars)
		{
			bars[idx].color = sf::Color::White;
		}
	}
}

int main()
{
	// seed RNG
	std::srand(std::time(0));

	// setup window
	sf::ContextSettings settings;
	settings.antialiasingLevel = 4;
	settings.majorVersion = 3;

	auto window = sf::RenderWindow(sf::VideoMode(800, 600), "Sorting Visualizer", sf::Style::Default, settings);
	window.setVerticalSyncEnabled(true);

	// setup collection of values
	std::vector<uint64_t> values;
	auto len = 100;
	for (auto i = 1; i <= len; ++i)
	{
		values.push_back(i);
	}
	std::shuffle(values.begin(), values.end(), std::mt19937(std::random_device()()));
	auto collection = Collection(values);

	// setup display
	auto display = Display(window, collection);

	// launch sorter on another thread
	sf::Thread sortAlgo(&sorter, std::make_tuple<Collection *, Display *>(&collection, &display));
	sortAlgo.launch();

	// event loop thing
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
			}
			else if (event.type == sf::Event::LostFocus)
			{
				// no reason to update the window at 60+fps if it's not in focus
				window.setFramerateLimit(12);
			}
			else if (event.type == sf::Event::GainedFocus)
			{
				window.setFramerateLimit(0);
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
