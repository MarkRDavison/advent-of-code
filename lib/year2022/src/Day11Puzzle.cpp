#include <2022/Day11Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <functional>
#include <cassert>
#include <algorithm>

namespace TwentyTwentyTwo {
	
	Day11Puzzle::Day11Puzzle() :
		core::PuzzleBase("Monkey in the Middle", 2022, 11) {
	}


	void Day11Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByLines(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0])));
	}

	void Day11Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct Monkey
	{
		std::size_t id{ 0 };
		std::vector<std::size_t> items;
		std::function<std::size_t(std::size_t)> operation;
		std::function<bool(std::size_t)> test;

		std::size_t trueMonkey{ 0 };
		std::size_t falseMonkey{ 0 };

		std::size_t inspections{ 0 };
	};

	std::size_t solve(const std::vector<std::string>& _inputLines, bool _part2, std::size_t _rounds)
	{
		std::vector<Monkey> monkeys;

		std::size_t naiveLowestCommonMultiple = 1;

		for (const auto& l : _inputLines)
		{
			const auto& p = ze::StringExtensions::splitStringByDelimeter(l, " :,");
			if (p.size() == 0)
			{
				// END OF MONKEY
			}
			else if (p[0] == "Monkey")
			{
				auto& m = monkeys.emplace_back();
				m.id = (std::size_t)std::stoul(p[1]);
			}
			else if (p[0] == "Starting")
			{
				auto& m = monkeys.back();
				for (std::size_t i = 2; i < p.size(); ++i)
				{
					m.items.push_back((std::size_t)std::stoul(p[i]));
				}
			}
			else if (p[0] == "Operation")
			{
				auto& m = monkeys.back();

				assert(p[1] == "new");
				assert(p[2] == "=");
				assert(p[3] == "old");

				const auto operand = p[4];
				const auto value = p[5];


				if (operand == "*")
				{
					if (value == "old")
					{
						m.operation = [=](std::size_t _old) -> std::size_t { return _old * _old; };
					}
					else
					{
						const auto numericValue = (std::size_t)std::stoul(value);
						m.operation = [=](std::size_t _old) -> std::size_t { return _old * numericValue; };
					}
				}
				else if (operand == "+")
				{
					if (value == "old")
					{
						m.operation = [=](std::size_t _old) -> std::size_t { return _old + _old; };
					}
					else
					{
						const auto numericValue = (std::size_t)std::stoul(value);
						m.operation = [=](std::size_t _old) -> std::size_t { return _old + numericValue; };
					}
				}
				else
				{
					assert(false);
				}

			}
			else if (p[0] == "Test")
			{
				auto& m = monkeys.back();

				assert(p[1] == "divisible");
				assert(p[2] == "by");

				const auto testValue = (std::size_t)std::stoul(p[3]);

				naiveLowestCommonMultiple *= testValue;

				m.test = [=](std::size_t _old) -> bool { return (_old % testValue) == 0; };
			}
			else if (p[0] == "If" && p[1] == "true")
			{
				auto& m = monkeys.back();
				m.trueMonkey = (std::size_t)std::stoul(p[5]);
			}
			else if (p[0] == "If" && p[1] == "false")
			{
				auto& m = monkeys.back();
				m.falseMonkey = (std::size_t)std::stoul(p[5]);
			}
			else
			{
				assert(false);
			}
		}

		for (std::size_t round = 0; round < _rounds; ++round)
		{
			
			for (std::size_t monkeyIndex = 0; monkeyIndex < monkeys.size(); ++monkeyIndex)
			{
				auto& currentMonkey = monkeys[monkeyIndex];
				while (!currentMonkey.items.empty())
				{
					currentMonkey.inspections++;
					const auto worryLevel = currentMonkey.items.front();
					currentMonkey.items.erase(currentMonkey.items.begin());

					auto newWorryLevel = currentMonkey.operation(worryLevel);
					if (!_part2)
					{
						newWorryLevel = newWorryLevel / 3;
					}

					std::size_t targetMonkey;
					if (currentMonkey.test(newWorryLevel))
					{
						targetMonkey = (std::size_t)currentMonkey.trueMonkey;
					}
					else
					{
						targetMonkey = (std::size_t)currentMonkey.falseMonkey;
					}

					if (_part2)
					{
						monkeys[targetMonkey].items.push_back(newWorryLevel % naiveLowestCommonMultiple);
					}
					else
					{
						monkeys[targetMonkey].items.push_back(newWorryLevel);
					}
				}
			}
		}

		std::sort(
			monkeys.begin(),
			monkeys.end(),
			[](const auto& _lhs, const auto& _rhs) { return _lhs.inspections < _rhs.inspections; });

		const auto& mostActiveMonkey = monkeys[monkeys.size() - 1];
		const auto& nextMostActiveMonkey = monkeys[monkeys.size() - 2];

		const auto monkeyBusinessLevel = mostActiveMonkey.inspections * nextMostActiveMonkey.inspections;

		return monkeyBusinessLevel;
	}

	std::pair<std::string, std::string> Day11Puzzle::fastSolve() {
		
		return {
			std::to_string(solve(m_InputLines, false, 20)),
			std::to_string(solve(m_InputLines, true, 10000))
		};
	}
}
