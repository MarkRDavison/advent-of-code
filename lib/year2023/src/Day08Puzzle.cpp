#include <2023/Day08Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_map>
#include <unordered_set>
#include <numeric>

namespace TwentyTwentyThree
{

	Day08Puzzle::Day08Puzzle() :
		core::PuzzleBase("Haunted Wasteland", 2023, 8)
	{
	}


	void Day08Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo)
	{
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day08Puzzle::setInputLines(const std::vector<std::string>& _inputLines)
	{
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	typedef std::unordered_map <std::string, std::pair<std::string, std::string>> Instructions;

	std::string Day08Puzzle::solvePart1(const std::vector<std::string>& input)
	{
		const auto dir = input[0];

		Instructions instructions;

		for (const auto& l : input)
		{
			const auto& p = StringExtensions::splitStringByDelimeter(l, " =,()");
			if (p.size() != 3) { continue; }

			instructions.emplace(p[0], std::pair<std::string, std::string>{ p[1], p[2] });
		}

		std::string start = "AAA";
		std::string end = "ZZZ";
		std::string current = start;

		std::size_t i = 0;

		long long part1 = 0;

		while (current != end)
		{
			const auto& next = instructions.at(current);
			const auto d = dir[i];
			if (d == 'L')
			{
				current = next.first;
			}
			else
			{
				current = next.second;
			}

			i = (i + 1) % dir.size();
			part1++;
		}

		return std::to_string(part1);
	}

	std::string Day08Puzzle::solvePart2(const std::vector<std::string>& input)
	{
		const auto dir = input[0];

		Instructions instructions;

		std::unordered_set<std::string> starting;
		std::unordered_set<std::string> ending;


		for (const auto& l : input)
		{
			const auto& p = StringExtensions::splitStringByDelimeter(l, " =,()");
			if (p.size() != 3) { continue; }

			instructions.emplace(p[0], std::pair<std::string, std::string>{ p[1], p[2] });

			if (p[0].ends_with('A'))
			{
				starting.insert(p[0]);
			}
			if (p[0].ends_with('Z'))
			{
				ending.insert(p[0]);
			}
		}

		long long part2 = 0;

		std::unordered_map<std::string, long long> cycleTime;
		for (const auto& start : starting)
		{
			std::size_t rounds = 0;
			std::size_t i = 0;
			auto current = start;
			while (!ending.contains(current))
			{
				const auto& next = instructions.at(current);
				const auto d = dir[i];
				if (d == 'L')
				{
					current = next.first;
				}
				else
				{
					current = next.second;
				}

				i = (i + 1) % dir.size();
				rounds++;
			}

			cycleTime.emplace(start, rounds);
		}

		std::vector<long long> factors;
		for (const auto& [k, v] : cycleTime)
		{
			factors.push_back(v);
		}

		long long val = factors[0];

		for (std::size_t i = 1; i < factors.size(); ++i)
		{
			val = std::lcm(val, factors[i]);
		}

		return std::to_string(val);
	}

	std::pair<std::string, std::string> Day08Puzzle::fastSolve() {

		return { solvePart1(m_InputLines), solvePart2(m_InputLines) };
	}
}
