#include <SortingVisualizer/Algorithms/QuickSort.hpp>

const std::size_t hoarePartition(Collection &collection, int64_t low, int64_t high)
{
	// why, yes i just copied this code from the internet - how could you tell?
	auto pivot = low;
	auto left = low - 1;
	auto right = high + 1;

	while (true)
	{
		do
		{
			++left;
		} while (collection.compare(left, pivot) == Order::LESS_THAN);

		do
		{
			--right;
		} while (collection.compare(right, pivot) == Order::GREATER_THAN);

		if (left >= right)
		{
			return right;
		}

		collection.swap(left, right);
	}

	return right;
}

const void quickSort(Collection &collection, int64_t low, int64_t high)
{
	if (high == -1) high = collection.length() - 1;
	if (low >= high) return;

	// don't yell at me for the formatting i'm too lazy to configure clang-tidy
	auto pivot = hoarePartition(collection, low, high);
	collection.doParallel(
		{[low, pivot](Collection &c) { quickSort(c, low, pivot); }, [pivot, high](Collection &c) { quickSort(c, pivot + 1, high); }});
}
