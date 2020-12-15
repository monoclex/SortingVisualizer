#ifndef SORTINGVISUALIZER_DISPLAY_H
#define SORTINGVISUALIZER_DISPLAY_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <stdint.h>

class Display
{
private:
	sf::RenderTarget &renderTarget;
	uint64_t maxBarValue;

public:
	Display(sf::RenderTarget &renderTarget, size_t barAmount, uint64_t maxBarValue);
	std::vector<uint64_t> bars;
	void draw() const;
};

#endif