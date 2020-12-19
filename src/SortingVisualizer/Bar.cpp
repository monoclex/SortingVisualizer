#include <SortingVisualizer/Bar.hpp>

std::vector<Bar> toBars(std::vector<uint64_t> values)
{
	std::vector<Bar> bars;
	bars.reserve(values.size());

	for (auto &value : values)
	{
		bars.push_back(Bar{value, sf::Color::White});
	}

	return bars;
}
