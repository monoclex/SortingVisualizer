#ifndef SORTINGVISUALIZER_COLLECTION_H
#define SORTINGVISUALIZER_COLLECTION_H

#include <functional>
#include <initializer_list>
#include <stdint.h>
#include <variant>
#include <vector>

enum class Order
{
	LESS_THAN,
	GREATER_THAN,
	EQUAL
};

// https://stackoverflow.com/a/64018031
struct Comparison
{
	std::size_t leftIdx;
	std::size_t rightIdx;
};

struct Swap
{
	std::size_t leftIdx;
	std::size_t rightIdx;
};

using Decision = std::variant<Comparison, Swap>;

class Collection
{
private:
	std::vector<uint64_t> values;
	std::vector<Decision> decisions;

public:
	Collection(std::vector<uint64_t> values);
	Collection(std::size_t valueCount);

	const std::size_t length() const;
	const uint64_t max() const;
	void doParallel(std::initializer_list<std::function<void(Collection)>> parallelActions);
	Order compare(std::size_t leftIdx, std::size_t rightIdx);
	void swap(std::size_t leftIdx, std::size_t rightIdx);
	void randomize();

	std::vector<uint64_t> contents() const;
};

#endif
