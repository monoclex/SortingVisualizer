
#include <SortingVisualizer/Collection.hpp>
#include <algorithm>
#include <random>
#include <stdint.h>
#include <vector>

Collection::Collection(std::vector<uint64_t> values) : values(values) { this->decisions = std::vector<Decision>(); }

Collection::Collection(std::size_t valueCount) : values()
{
	this->values.reserve(valueCount);

	for (auto i = 1; i <= valueCount; i++)
	{
		this->values.push_back(i);
	}
}

const std::size_t Collection::length() const { return this->values.size(); }

void Collection::doParallel(std::initializer_list<std::function<void(Collection)>> parallelActions) {}

Order Collection::compare(std::size_t leftIdx, std::size_t rightIdx)
{
	this->decisions.push_back(Comparison{leftIdx, rightIdx});

	auto left = this->values[leftIdx];
	auto right = this->values[rightIdx];

	if (left < right) return Order::LESS_THAN;
	if (left > right) return Order::GREATER_THAN;
	return Order::EQUAL;
}

void Collection::swap(std::size_t leftIdx, std::size_t rightIdx)
{
	this->decisions.push_back(Swap{leftIdx, rightIdx});

	std::swap(this->values[leftIdx], this->values[rightIdx]);
}

const uint64_t Collection::max() const { return *std::max_element(this->values.begin(), this->values.end()); }

std::vector<uint64_t> Collection::contents() const { return this->values; }

void Collection::randomize() { std::shuffle(this->values.begin(), this->values.end(), std::mt19937(std::random_device()())); }

const std::vector<Decision> &Collection::getDecisions() const { return this->decisions; }

//  std::size_t length() ;
//  void doParallel(std::initializer_list<std::function<void(Collection)>> parallelActions) ;

// CollectionItem &operator[](std::size_t idx);
//  CollectionItem &operator[](std::size_t idx) ;