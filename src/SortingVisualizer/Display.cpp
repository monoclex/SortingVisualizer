#include <SortingVisualizer/Display.hpp>

Display::Display(sf::RenderTarget &renderTarget, Collection &collection)
	: renderTarget(renderTarget), bars(std::make_shared<std::vector<Bar>>(toBars(collection.contents()))), maxBarValue(collection.max())
{
}

void Display::setBars(std::vector<Bar> bars) { *this->bars.get() = bars; }

void Display::draw()
{
	auto bars = *this->bars.get();
	auto size = this->renderTarget.getSize();
	auto barCount = (float)bars.size();

	// when we draw the bars, we want each bar to have one pixel of spacing inbetween each other,
	// and one pixel of spacing at the start and the end
	auto spacing = 1.0f;
	auto pixelsOfSpacing = spacing + barCount * spacing;
	auto pixelsOfBoxes = size.x - pixelsOfSpacing;
	auto barWidth = pixelsOfBoxes / barCount;

	for (auto i = 0; auto bar : bars)
	{
		auto barX = spacing + i * (barWidth + spacing);
		auto barY = (float)bar.value / (float)maxBarValue * size.y;

		sf::RectangleShape rectangle;
		rectangle.setPosition(barX, size.y - barY);
		rectangle.setSize(sf::Vector2f(barWidth, barY));
		rectangle.setFillColor(bar.color);

		this->renderTarget.draw(rectangle);

		++i;
	}
}
