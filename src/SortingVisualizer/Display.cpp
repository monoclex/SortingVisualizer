#include <SFML/Graphics/RectangleShape.hpp>
#include <SortingVisualizer/Display.hpp>
#include <iostream>
#include <stdint.h>

Display::Display(sf::RenderTarget &renderTarget, size_t barAmount, uint64_t maxBarValue) : renderTarget(renderTarget)
{
	this->bars = std::vector<uint64_t>(barAmount);
	this->maxBarValue = maxBarValue;
}

void Display::draw() const
{
	auto size = this->renderTarget.getSize();
	auto barCount = (float)this->bars.size();

	// when we draw the bars, we want each bar to have one pixel of spacing inbetween each other,
	// and one pixel of spacing at the start and the end
	auto spacing = 1.0f;
	auto pixelsOfSpacing = spacing + barCount * spacing;
	auto pixelsOfBoxes = size.x - pixelsOfSpacing;
	auto barWidth = pixelsOfBoxes / barCount;

	for (auto i = 0; auto bar : this->bars)
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