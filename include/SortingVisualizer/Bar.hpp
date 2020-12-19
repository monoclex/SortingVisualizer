#pragma once
#include <SFML/Graphics/Color.hpp>
#include <stdint.h>
#include <vector>

/**
 * Representation of a bar - it has a value, and a color.
 */
struct Bar
{
	uint64_t value;
	sf::Color color;
};

/**
 * Converts a series of values into a series of bars.
 */
std::vector<Bar> toBars(std::vector<uint64_t> values);
