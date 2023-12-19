#include <2023/Day19Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_map>
#include <algorithm>
#include <cassert>
#include <ranges>
#include <array>

#define CHARS std::string("xmas")

namespace TwentyTwentyThree {
	
	Day19Puzzle::Day19Puzzle() :
		core::PuzzleBase("Aplenty", 2023, 19) {
	}


	void Day19Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day19Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct Rule
	{
		std::string input;
		char op{'?'};
		long long val;
		std::string nextWorkflow;
	};

	struct Workflow
	{
		std::string name;
		std::vector<Rule> rules;
	};

	typedef std::unordered_map<std::string, long long> Ratings;

	Workflow getWorkflow(const std::vector<Workflow>& workflows, const std::string& name)
	{
		for (const auto& w : workflows)
		{
			if (w.name == name)
			{
				return w;
			}
		}

		assert(false);
		return {};
	}

	bool isAccepted(const std::vector<Workflow>& workflows, const Ratings& ratings)
	{
		const std::string starting = "in";

		std::string curr = starting;

		while (true)
		{
			if (curr == "R")
			{
				return false;
			}
			else if (curr == "A")
			{
				return true;
			}

			const auto& workflow = getWorkflow(workflows, curr);

			for (const auto& rule : workflow.rules)
			{
				if (rule.op == '?')
				{
					curr = rule.nextWorkflow;
					break;
				}
				const auto ratingValue = ratings.at(rule.input);

				bool rulePassed = false;

				if (rule.op == '>')
				{
					rulePassed = ratingValue > rule.val;
				}
				else if (rule.op == '<')
				{
					rulePassed = ratingValue < rule.val;
				}
				else
				{
					assert(false);
				}

				if (rulePassed)
				{
					curr = rule.nextWorkflow;
					break;
				}
			}
		}

		assert(false);
		return false;
	}

	struct RangeNode
	{
		std::array<long long, 4> min = { 1,1,1,1 };
		std::array<long long, 4> max = { 4000, 4000, 4000, 4000 };
	};

	long long recurser(
		const std::vector<Workflow>& workflows,
		const std::string& currentWorkflow,
		RangeNode range
	)
	{
		long long value = 0;

		if (currentWorkflow == "R")
		{
			return 0;
		}

		if (currentWorkflow == "A")
		{
			value = 1;

			for (std::size_t i = 0; i < 4; ++i)
			{
				value *= (range.max.at(i) - range.min.at(i) + 1);
			}

			return value;
		}

		const auto& workflow = getWorkflow(workflows, currentWorkflow);

		for (const auto& r : workflow.rules | std::views::take(workflow.rules.size() - 1))
		{
			const auto index = CHARS.find(r.input);

			if (r.op == '<')
			{
				const auto minimum = range.min.at(index);
				const auto maximum = range.max.at(index);

				if (minimum < r.val)
				{
					RangeNode newRange(range);
					newRange.min[index] = minimum;
					newRange.max[index] = r.val - 1;

					value += recurser(workflows, r.nextWorkflow, newRange);
				}

				if (maximum >= r.val)
				{
					range.min[index] = r.val;
					range.max[index] = maximum;
				}
				else
				{
					break;
				}
			}
			else
			{
				const auto minimum = range.min.at(index);
				const auto maximum = range.max.at(index);

				if (maximum > r.val)
				{
					RangeNode newRange(range);
					newRange.min[index] = r.val + 1;
					newRange.max[index] = maximum;

					value += recurser(workflows, r.nextWorkflow, newRange);
				}

				if (minimum <= r.val)
				{
					range.min[index] = minimum;
					range.max[index] = r.val;
				}
				else
				{
					break;
				}
			}
		}

		value += recurser(workflows, workflow.rules.back().nextWorkflow, range);

		return value;
	}

	std::pair<std::string, std::string> Day19Puzzle::fastSolve() {
		std::vector<Workflow> workflows;

		std::vector<Ratings> ratings;

		bool workflowMode = true;

		for (const auto& l : m_InputLines)
		{
			if (l.starts_with('{'))
			{
				workflowMode = false;
			}

			const auto& workflowParts = StringExtensions::splitStringByDelimeter(l, "{},");

			if (workflowParts.empty())
			{
				workflowMode = false;
				continue;
			}

			if (workflowMode)
			{
				auto& w = workflows.emplace_back();
				w.name = workflowParts[0];

				assert(workflowParts.size() > 2);

				for (const auto& rule : workflowParts | std::views::drop(1))
				{
					bool lessThan = rule.find('<') != std::string::npos;
					bool greaterThan = rule.find('>') != std::string::npos;


					const auto& ruleParts = StringExtensions::splitStringByDelimeter(rule, ":<>");

					auto& r = w.rules.emplace_back();

					if (ruleParts.size() == 3)
					{
						assert(lessThan != greaterThan);

						r.input = ruleParts[0];
						if (lessThan)
						{
							r.op = '<';
						}
						else if (greaterThan)
						{
							r.op = '>';
						}
						r.val = std::stoll(ruleParts[1]);
						r.nextWorkflow = ruleParts[2];
					}
					else
					{
						assert(ruleParts.size() == 1);
						r.nextWorkflow = ruleParts[0];
					}
				}
			}
			else
			{
				auto& rating = ratings.emplace_back();
				const auto& ratingParts = StringExtensions::splitStringByDelimeter(l, "{=,}");
				assert(ratingParts.size() % 2 == 0);

				for (std::size_t i = 0; i < ratingParts.size(); i += 2)
				{
					rating[ratingParts[i + 0]] = std::stoll(ratingParts[i + 1]);
				}
			}
		}


		long long part1 = 0;

		for (const auto& rating : ratings)
		{
			if (isAccepted(workflows, rating))
			{
				const auto score =
					rating.at("x") +
					rating.at("m") +
					rating.at("a") +
					rating.at("s");
				part1 += score;
			}
		}
		
		long long part2 = recurser(workflows, "in", RangeNode());

		return { std::to_string(part1), std::to_string(part2) };
	}
}
