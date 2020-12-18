#include <SortingVisualizer/Algorithms/BubbleSort.hpp>
#include <SortingVisualizer/Collection.hpp>

const void bubbleSort(Collection &collection)
{
	for (auto i = 0; i < collection.length(); i++)
	{
		for (auto j = i; j < collection.length(); j++)
		{
			if (collection.compare(i, j) == Order::GREATER_THAN)
			{
				collection.swap(i, j);
			}
		}
	}
}