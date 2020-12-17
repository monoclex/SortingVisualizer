
#include <SortingVisualizer/Collection.hpp>
#include <algorithm>
#include <stdint.h>
#include <vector>

CollectionItem::CollectionItem(uint64_t value) { this->value = value; }

Comparison CollectionItem::compare(CollectionItem &other) const
{
	if (this->value < other.value) return Comparison::LESS_THAN;
	if (this->value > other.value) return Comparison::GREATER_THAN;
	return Comparison::EQUAL;
}

Collection::Collection(std::vector<uint64_t> values) : values()
{
	this->decisions = std::vector<uint8_t /*Decision*/>();

	for (auto &value : values)
	{
		this->values.push_back(CollectionItem(value));
	}
}

std::size_t Collection::length() const { return this->values.size(); }

void Collection::doParallel(std::initializer_list<std::function<void(Collection)>> parallelActions) {}

Comparison Collection::compare(std::size_t leftIdx, std::size_t rightIdx) { return this->values[leftIdx].compare(this->values[rightIdx]); }

void Collection::swap(std::size_t leftIdx, std::size_t rightIdx) { std::swap(this->values[leftIdx], this->values[rightIdx]); }

CollectionItem &Collection::operator[](std::size_t idx) { return this->values[idx]; }

//  std::size_t length() ;
//  void doParallel(std::initializer_list<std::function<void(Collection)>> parallelActions) ;

// CollectionItem &operator[](std::size_t idx);
//  CollectionItem &operator[](std::size_t idx) ;