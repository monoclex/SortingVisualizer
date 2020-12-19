#include <SortingVisualizer/Algorithms/BubbleSort.hpp>
#include <SortingVisualizer/Collection.hpp>

const void bubbleSort(Collection &collection)
{
	// auto swapped = false;
	// auto last = collection.length() - 1;

	// do
	// {
	// 	swapped = false;

	// 	for (auto i = 0; i < last; i++)
	// 	{
	// 		if (collection.compare(i, i + 1) == Order::GREATER_THAN)
	// 		{
	// 			collection.swap(i, i + 1);
	// 			swapped = true;
	// 		}
	// 	}

	// 	last -= 1;
	// } while (swapped);

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