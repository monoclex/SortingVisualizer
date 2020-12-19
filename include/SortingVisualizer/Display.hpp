#pragma once
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SortingVisualizer/Bar.hpp>
#include <SortingVisualizer/Collection.hpp>
#include <memory>
#include <stdint.h>

/**
 * Class that contains bars, and can draw the bars. It also allows setting the bars from another thread, so that
 * the sorting and drawing are independent of one another.
 */
class Display
{
private:
	sf::RenderTarget &renderTarget;
	std::shared_ptr<std::vector<Bar>> bars;
	const uint64_t maxBarValue;

public:
	Display(sf::RenderTarget &renderTarget, Collection &collection);

	void setBars(std::vector<Bar> bars);
	void draw();
};
