
#include <SortingVisualizer/Collection.hpp>

Collection::Collection(std::vector<uint64_t> values) : values(values) { this->decisions = std::vector<Decision>(); }

const std::size_t Collection::length() const { return this->values.size(); }

const uint64_t Collection::max() const { return *std::max_element(this->values.begin(), this->values.end()); }

std::vector<uint64_t> Collection::contents() const { return this->values; }

const std::vector<Decision> &Collection::getDecisions() const { return this->decisions; }

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

void Collection::doParallel(std::initializer_list<std::function<void(Collection)>> parallelActions) {}
