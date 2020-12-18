#include <SFML/Graphics/RectangleShape.hpp>
#include <SortingVisualizer/Collection.hpp>
#include <SortingVisualizer/Display.hpp>
#include <algorithm>
#include <iostream>
#include <stdint.h>

Display::Display(sf::RenderTarget &renderTarget, Collection &collection)
	: renderTarget(renderTarget), collection(collection), maxBarValue(collection.max())
{
}

void Display::draw()
{
	auto size = this->renderTarget.getSize();
	auto barCount = (float)this->collection.length();

	// when we draw the bars, we want each bar to have one pixel of spacing inbetween each other,
	// and one pixel of spacing at the start and the end
	auto spacing = 1.0f;
	auto pixelsOfSpacing = spacing + barCount * spacing;
	auto pixelsOfBoxes = size.x - pixelsOfSpacing;
	auto barWidth = pixelsOfBoxes / barCount;

	for (auto i = 0; auto bar : this->collection.contents())
	{
		auto barX = spacing + i * (barWidth + spacing);
		auto barY = (float)bar / (float)maxBarValue * size.y;

		sf::RectangleShape rectangle;
		rectangle.setPosition(barX, size.y - barY);
		rectangle.setSize(sf::Vector2f(barWidth, barY));
		rectangle.setFillColor(sf::Color::Green);

		this->renderTarget.draw(rectangle);

		++i;
	}
}