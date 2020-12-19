
#include <SortingVisualizer/Collection.hpp>
#include <algorithm>
#include <stdexcept>

Collection::Collection(std::vector<uint64_t> values) : values(values), decisions() {}

const std::size_t Collection::length() const { return this->values.size(); }

const uint64_t Collection::max() const { return *std::max_element(this->values.begin(), this->values.end()); }

std::vector<uint64_t> Collection::contents() const { return this->values; }

std::vector<Decision> Collection::getDecisions(const std::size_t parallelWorkers) const
{
	std::vector<Decision> resultantDecisions;

	for (auto i : this->decisions.decisions)
	{
		if (std::holds_alternative<SingleDecision>(i))
		{
			auto decision = std::get<SingleDecision>(i);

			resultantDecisions.push_back(decision);
		}
		else if (std::holds_alternative<std::vector<InternalDecisions>>(i))
		{
			auto queue = std::get<std::vector<InternalDecisions>>(i);
			auto parallelConsume = std::min(queue.size(), parallelWorkers);

			std::vector<std::vector<std::variant<SingleDecision, std::vector<InternalDecisions>>>> consumers;
			consumers.reserve(parallelWorkers);

			for (auto i = 0; i < parallelConsume; i++)
			{
				consumers.push_back(queue.front().decisions);
				queue.erase(queue.begin());
			}

			while (!consumers.empty() || !queue.empty())
			{
				std::vector<SingleDecision> parallelDecision;

				for (auto i = 0; i < consumers.size(); i++)
				{
					auto &c = consumers[i];

					if (c.empty())
					{
						consumers.erase(consumers.begin() + i);
						--i;

						if (!queue.empty())
						{
							consumers.push_back(queue.front().decisions);
							queue.erase(queue.begin());
						}

						continue;
					}

					std::variant<SingleDecision, std::vector<InternalDecisions>> element = c[0];

					if (std::holds_alternative<SingleDecision>(element))
					{
						auto decision = std::get<SingleDecision>(element);

						parallelDecision.push_back(decision);
					}
					else if (std::holds_alternative<std::vector<InternalDecisions>>(element))
					{
						auto decisions = std::get<std::vector<InternalDecisions>>(element);

						for (auto d : decisions)
						{
							queue.push_back(d);
						}
					}
					else
					{
						throw std::logic_error("couldn't match on variant");
					}

					c.erase(c.begin());

					if (c.empty())
					{
						consumers.erase(consumers.begin() + i);
						--i;
					}
				}

				while (consumers.size() != std::min(consumers.size() + queue.size(), parallelWorkers) && !queue.empty())
				{
					consumers.push_back(queue.front().decisions);
					queue.erase(queue.begin());
				}

				if (parallelDecision.size() == 0)
				{
				}
				else if (parallelDecision.size() == 1)
				{
					resultantDecisions.push_back(parallelDecision.front());
				}
				else
				{
					resultantDecisions.push_back(parallelDecision);
				}
			}
		}
	}

	return resultantDecisions;
}

Order Collection::compare(std::size_t leftIdx, std::size_t rightIdx)
{
	if (leftIdx >= this->values.size()) throw "leftIdx out of range";
	if (rightIdx >= this->values.size()) throw "rightIdx out of range";

	this->decisions.decisions.push_back(Comparison{leftIdx, rightIdx});

	auto left = this->values[leftIdx];
	auto right = this->values[rightIdx];

	if (left < right) return Order::LESS_THAN;
	if (left > right) return Order::GREATER_THAN;
	return Order::EQUAL;
}

void Collection::swap(std::size_t leftIdx, std::size_t rightIdx)
{
	this->decisions.decisions.push_back(Swap{leftIdx, rightIdx});

	std::swap(this->values[leftIdx], this->values[rightIdx]);
}

void Collection::followThroughDecision(const SingleDecision &decision)
{
	if (std::holds_alternative<Swap>(decision))
	{
		auto swap = std::get<Swap>(decision);

		std::swap(this->values[swap.leftIdx], this->values[swap.rightIdx]);
	}
	else
	{
		// other is a comparison we don't care about
	}
}

void Collection::followThroughDecisions(const std::vector<InternalDecisions> &decisions)
{
	for (auto &otherDecisions : decisions)
	{
		for (auto &i : otherDecisions.decisions)
		{
			if (std::holds_alternative<SingleDecision>(i))
			{
				auto decision = std::get<SingleDecision>(i);
				this->followThroughDecision(decision);
			}
			else if (std::holds_alternative<std::vector<InternalDecisions>>(i))
			{
				auto decisions = std::get<std::vector<InternalDecisions>>(i);
				this->followThroughDecisions(decisions);
			}
			else
			{
				throw std::logic_error("couldn't match on variant");
			}
		}
	}
}

void Collection::doParallel(std::initializer_list<std::function<void(Collection &)>> parallelActions)
{
	std::vector<InternalDecisions> parallelDecisions;
	parallelDecisions.reserve(parallelActions.size());

	for (auto &p : parallelActions)
	{
		Collection collection(this->values);
		p(collection);

		parallelDecisions.push_back(collection.decisions);
	}

	this->followThroughDecisions(parallelDecisions);
	this->decisions.decisions.push_back(parallelDecisions);
}
