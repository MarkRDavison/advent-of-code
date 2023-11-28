#include <2022/Day04Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_set>

namespace TwentyTwentyTwo {
	
	Day04Puzzle::Day04Puzzle() :
		core::PuzzleBase("Camp Cleanup", 2022, 4) {
	}


	void Day04Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day04Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day04Puzzle::fastSolve() {
		int part1 = 0;
		int part2 = 0;
		for (const auto& l : m_InputLines)
		{
			const auto& p = StringExtensions::splitStringByDelimeter(l, "-,");
			const int e1start = std::stoi(p[0]);
			const int e1end = std::stoi(p[1]);
			const int e2start = std::stoi(p[2]);
			const int e2end = std::stoi(p[3]);

			if ((e1start <= e2start && e2end <= e1end) ||
				(e2start <= e1start && e1end <= e2end))
			{
				part1++;
			}

			std::unordered_set<int> overlap;

			for (int i = e1start; i <= e1end; ++i)
			{
				overlap.insert(i);
			}
			for (int i = e2start; i <= e2end; ++i)
			{
				if (overlap.find(i) != overlap.end())
				{
					part2++;
					break;
				}
			}
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
