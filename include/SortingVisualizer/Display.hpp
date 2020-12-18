#ifndef SORTINGVISUALIZER_DISPLAY_H
#define SORTINGVISUALIZER_DISPLAY_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SortingVisualizer/Collection.hpp>
#include <stdint.h>

class Display
{
private:
	sf::RenderTarget &renderTarget;
	const Collection &collection;
	const uint64_t maxBarValue;

public:
	Display(sf::RenderTarget &renderTarget, Collection &collection);
	void draw();
};

#endif