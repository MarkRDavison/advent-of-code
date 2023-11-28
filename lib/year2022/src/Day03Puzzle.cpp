#include <2022/Day03Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <cassert>
#include <unordered_set>
#include <unordered_map>

namespace TwentyTwentyTwo {
	
	Day03Puzzle::Day03Puzzle() :
		core::PuzzleBase("Rucksack Reorganization", 2022, 3) {
	}


	void Day03Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day03Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	int priority(char _c)
	{
		if ('a' <= _c && _c <= 'z')
		{
			return (_c - 'a') + 1;
		}
		if ('A' <= _c && _c <= 'Z')
		{
			return (_c - 'A') + 27;
		}
		return 0;
	}

	std::pair<std::string, std::string> Day03Puzzle::fastSolve() {

		int part1 = 0;
		int part2 = 0;

		for (const auto& l : m_InputLines)
		{
			assert(l.size() % 2 == 0);
			const auto compartmentSize = l.size() / 2;

			const auto c1 = l.substr(0, compartmentSize);
			const auto c2 = l.substr(compartmentSize);

			std::unordered_set<char> presence;

			for (const auto c : c1)
			{
				if (c2.find(c) != std::string::npos)
				{
					presence.insert(c);
				}
			}

			assert(presence.size() == 1);

			part1 += priority(*presence.begin());
		}


		for (std::size_t i = 0; i < m_InputLines.size(); i += 3)
		{
			const auto l1 = m_InputLines[i + 0];
			const auto l2 = m_InputLines[i + 1];
			const auto l3 = m_InputLines[i + 2];

			std::unordered_map<char, bool[3]> presence;

			for (const auto c : l1)
			{
				presence[c][0] = true;
			}
			for (const auto c : l2)
			{
				presence[c][1] = true;
			}
			for (const auto c : l3)
			{
				presence[c][2] = true;
			}

			for (const auto& [c, present] : presence)
			{
				if (present[0] && present[1] && present[2])
				{
					part2 += priority(c);
					break;
				}
			}
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
