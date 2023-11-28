#include <2022/Day21Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <cassert>
#include <map>
#include <queue>
#include <unordered_map>
#include <unordered_set>
#include <functional>

#define RootMonkeyName "root"
#define HumanMonkeyName "humn"

namespace TwentyTwentyTwo {
	
	Day21Puzzle::Day21Puzzle() :
		core::PuzzleBase("Monkey Math", 2022, 21) {
	}


	void Day21Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day21Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct MonkeyJob {
		std::string name;
		bool constant;
		int64_t val;
		std::string lhsName;
		std::string rhsName;
		std::string op;
	};

	std::vector<MonkeyJob> parse(const std::vector<std::string>& _input)
	{
		std::vector<MonkeyJob> jobs;
		for (const auto& l : _input)
		{
			auto& j = jobs.emplace_back();
			const auto& p = StringExtensions::splitStringByDelimeter(l, " :");
			if (p.size() == 2)
			{
				j.name = p[0];
				j.constant = true;
				j.val = std::stoll(p[1]);
			}
			else if (p.size() == 4)
			{
				j.name = p[0];
				j.constant = false;
				j.lhsName = p[1];
				j.op = p[2];
				j.rhsName = p[3];
			}
			else
			{
				assert(false);
			}
		}
		return jobs;
	}

	struct SolveInfo
	{
		int64_t rootYell{ 0 };
		int64_t rootLhsYell{ 0 };
		int64_t rootRhsYell{ 0 };
	};

	SolveInfo solveWithEndingInfo(const std::string& _targetMonkey, const std::vector<MonkeyJob>& _jobs, const std::string& _rootLhs, const std::string& _rootRhs)
	{
		std::unordered_map<std::string, int64_t> memoized;
		std::unordered_map<std::string, std::function<int64_t()>> calculations;

		for (const auto& j : _jobs)
		{
			if (j.constant)
			{
				auto v = j.val;
				memoized[j.name] = j.val;
				calculations[j.name] = [v]() -> int64_t { return v; };
			}
			else
			{
				calculations[j.name] =
					[&calculations, &memoized, j]() -> int64_t
				{
					if (memoized.find(j.name) != memoized.end())
					{
						return memoized[j.name];
					}

					int64_t val = 0;
					const auto lhs = calculations[j.lhsName]();
					const auto rhs = calculations[j.rhsName]();
					if (j.op == "+")
					{
						val = lhs + rhs;
					}
					else if (j.op == "-")
					{
						val = lhs - rhs;
					}
					else if (j.op == "*")
					{
						val = lhs * rhs;
					}
					else if (j.op == "/")
					{
						val = lhs / rhs;
					}
					else if (j.op == "=")
					{
						val = lhs == rhs;
					}
					else
					{
						assert(false);
					}
					if (memoized.find(j.name) == memoized.end())
					{
						memoized[j.name] = val;
					}
					return val;
				};
			}
		}

		auto answer = calculations[_targetMonkey]();

		const auto lhs = memoized[_rootLhs];
		const auto rhs = memoized[_rootRhs];

		return SolveInfo{
			.rootYell = answer,
			.rootLhsYell = lhs,
			.rootRhsYell = rhs
		};
	}

	int64_t solve(const std::string& _targetMonkey, const std::vector<MonkeyJob>& _jobs)
	{
		std::string rootLhs;
		std::string rootRhs;
		for (auto& j : _jobs)
		{
			if (j.name == _targetMonkey)
			{
				rootLhs = j.lhsName;
				rootRhs = j.rhsName;
				break;
			}
		}

		return solveWithEndingInfo(_targetMonkey, _jobs, rootLhs, rootRhs).rootYell;
	}

	std::pair<std::string, std::string> Day21Puzzle::fastSolve() {

		const std::vector<MonkeyJob> jobs = parse(m_InputLines);
		std::vector<MonkeyJob> jobs2(jobs);
		std::unordered_map<std::string, MonkeyJob*> monkeys;

		auto part1 = solve(RootMonkeyName, jobs);

		std::size_t humanJobIndex = 0;
		std::size_t i = 0;
		std::string rootLhs;
		std::string rootRhs;
		for (auto& j : jobs2)
		{
			monkeys[j.name] = &jobs2[i];
			if (j.name == RootMonkeyName)
			{
				j.op = "=";
				rootLhs = j.lhsName;
				rootRhs = j.rhsName;
			}

			if (strcmp(j.name.c_str(), "humn") == 0)
			{
				humanJobIndex = i;
			}

			i++;
		}

		MonkeyJob& humanJob = jobs2[humanJobIndex];


		// TODO: Lots of stuff here might not work depending on what side of the tree etc the humn node is on
		humanJob.val = 10;
		auto exampleSolve1 = solveWithEndingInfo(RootMonkeyName, jobs2, rootLhs, rootRhs);
		humanJob.val = 20;
		auto exampleSolve2 = solveWithEndingInfo(RootMonkeyName, jobs2, rootLhs, rootRhs);
		humanJob.val = 30;
		auto exampleSolve3 = solveWithEndingInfo(RootMonkeyName, jobs2, rootLhs, rootRhs);

		int64_t range = 1;

		while (range * 10 < exampleSolve1.rootRhsYell / 10)
		{
			range *= 10;
		}

		int64_t valueToCheck = range;
		int64_t prev = solveWithEndingInfo(RootMonkeyName, jobs2, rootLhs, rootRhs).rootLhsYell;;
		while (true)
		{
			humanJob.val = valueToCheck;
			auto next = solveWithEndingInfo(RootMonkeyName, jobs2, rootLhs, rootRhs);
			std::cout << "checked " << valueToCheck << ", is " << next.rootLhsYell << " vs " << exampleSolve1.rootRhsYell << std::endl;
			if (range == 1)
			{
				if (next.rootLhsYell == exampleSolve1.rootRhsYell)
				{
					break;
				}
			}
			else if (
				(prev > exampleSolve1.rootRhsYell && exampleSolve1.rootRhsYell > next.rootLhsYell) ||
				(prev < exampleSolve1.rootRhsYell && exampleSolve1.rootRhsYell < next.rootLhsYell))
			{
				if (range > 1)
				{
					valueToCheck -= range;
					range /= 10;
					continue;
				}
			}
			valueToCheck += range;
			prev = next.rootLhsYell;
		}

		return { std::to_string(part1), std::to_string(valueToCheck) };
	}
}
