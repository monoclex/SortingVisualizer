#ifndef SORTINGVISUALIZER_DISPLAY_H
#define SORTINGVISUALIZER_DISPLAY_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SortingVisualizer/Bar.hpp>
#include <SortingVisualizer/Collection.hpp>
#include <memory>
#include <stdint.h>

class Display
{
private:
	sf::RenderTarget &renderTarget;
	std::shared_ptr<std::vector<Bar>> bars;
	const uint64_t maxBarValue;

public:
	Display(sf::RenderTarget &renderTarget, Collection &collection);
	void draw();
	void setBars(std::vector<Bar> bars);
};

#endif