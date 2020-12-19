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
using SingleDecision = std::variant<Comparison, Swap>;
using Decision = std::variant<SingleDecision, std::vector<SingleDecision>>;

class InternalDecisions
{
public:
	std::vector<std::variant<SingleDecision, std::vector<InternalDecisions>>> decisions;
};

class Collection
{
private:
	std::vector<uint64_t> initialValues;
	std::vector<uint64_t> values;
	InternalDecisions decisions;
	void followThroughDecision(const SingleDecision &decision);
	void followThroughDecisions(const std::vector<InternalDecisions> &decisions);

public:
	Collection(std::vector<uint64_t> values);

	const std::size_t length() const;
	const uint64_t max() const;

	std::vector<uint64_t> contents() const;
	std::vector<Decision> getDecisions(const std::size_t parallelWorkers = 1) const;

	Order compare(std::size_t leftIdx, std::size_t rightIdx);
	void swap(std::size_t leftIdx, std::size_t rightIdx);

	void doParallel(std::initializer_list<std::function<void(Collection &)>> parallelActions);
};
