#include <SortingVisualizer/Collection.hpp>

const void bubbleSort(Collection collection)
{
	for (auto i = 0; i < collection.length(); i++)
	{
		for (auto j = i; j < collection.length(); j++)
		{
			auto comparison = collection.compare(i, j);

			if (comparison == Comparison::GREATER_THAN)
			{
				collection.swap(i, j);
			}
		}
	}
}