#include <SortingVisualizer/Algorithms/BubbleSort.hpp>

const void bubbleSort(Collection &collection)
{
	auto swapped = true;

	while (swapped)
	{
		swapped = false;

		for (auto i = 0; i < collection.length(); i++)
		{
			if (collection.compare(i, i + 1) == Order::GREATER_THAN)
			{
				collection.swap(i, i + 1);
				swapped = true;
			}
		}
	}
}
