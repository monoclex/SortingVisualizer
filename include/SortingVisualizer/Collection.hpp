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

/**
 * Metadata that tracks when a comparison was made.
 */
struct Comparison
{
	std::size_t leftIdx;
	std::size_t rightIdx;
};

/**
 * Metadata that tracks when a swap was performed.
 */
struct Swap
{
	std::size_t leftIdx;
	std::size_t rightIdx;
};

// https://stackoverflow.com/a/64018031
using SingleDecision = std::variant<Comparison, Swap>;
using Decision = std::variant<SingleDecision, std::vector<SingleDecision>>;

/**
 * Some weird class that allows the parallel sorting magic crud or something,,,
 */
class InternalDecisions
{
public:
	std::vector<std::variant<SingleDecision, std::vector<InternalDecisions>>> decisions;
};

/**
 * A class that encapsulates its contents, and exists as a container to
 *
 * - Abstractly perform operations, such as comparing and swapping
 * - Record the performed operations to play back later
 * - Will play back the performed operation with the maximum amount of requested parallelism
 */
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
