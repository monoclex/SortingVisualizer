#ifndef SORTINGVISUALIZER_COLLECTION_H
#define SORTINGVISUALIZER_COLLECTION_H

#include <functional>
#include <initializer_list>
#include <stdint.h>
#include <variant>
#include <vector>

enum class Comparison
{
	LESS_THAN,
	GREATER_THAN,
	EQUAL
};

class CollectionItem
{
private:
	uint64_t value;
	// std::vector<Decision> &parentDecisions;

public:
	CollectionItem(uint64_t value);

	Comparison compare(CollectionItem &other) const;

	// inline bool operator<( CollectionItem &lhs,  CollectionItem &rhs);
	// inline bool operator>( CollectionItem &lhs,  CollectionItem &rhs) { return rhs < lhs; }
	// inline bool operator<=( CollectionItem &lhs,  CollectionItem &rhs) { return !(lhs > rhs); }
	// inline bool operator>=( CollectionItem &lhs,  CollectionItem &rhs) { return !(lhs < rhs); }
};

// https://stackoverflow.com/a/64018031
// struct Comparison
// {
// 	std::size_t leftIdx;
// 	std::size_t rightIdx;
// };

// using Decision = std::variant<Comparison>;

class Collection
{
private:
	std::vector<CollectionItem> values;
	std::vector<uint8_t /*Decision*/> decisions;

public:
	Collection(std::vector<uint64_t> values);

	std::size_t length() const;
	void doParallel(std::initializer_list<std::function<void(Collection)>> parallelActions);
	Comparison compare(std::size_t leftIdx, std::size_t rightIdx);
	void swap(std::size_t leftIdx, std::size_t rightIdx);

	CollectionItem &operator[](std::size_t idx);
};

#endif
