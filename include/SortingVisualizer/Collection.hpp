#pragma once
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

// https://stackoverflow.com/a/64018031
using Decision = std::variant<Comparison, Swap>;

class Collection
{
private:
	std::vector<uint64_t> initialValues;
	std::vector<uint64_t> values;
	std::vector<Decision> decisions;

public:
	Collection(std::vector<uint64_t> values);

	const std::size_t length() const;
	const uint64_t max() const;

	std::vector<uint64_t> contents() const;
	const std::vector<Decision> &getDecisions() const;

	Order compare(std::size_t leftIdx, std::size_t rightIdx);
	void swap(std::size_t leftIdx, std::size_t rightIdx);

	void doParallel(std::initializer_list<std::function<void(Collection)>> parallelActions);
};
