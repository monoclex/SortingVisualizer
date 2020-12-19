#pragma once
#include <SortingVisualizer/Collection.hpp>

/**
 * Performs Quicksort. As an implementation detail, it uses Hoare's partitioning algorithm.
 */
const void quickSort(Collection &collection, int64_t low = 0, int64_t high = -1);
