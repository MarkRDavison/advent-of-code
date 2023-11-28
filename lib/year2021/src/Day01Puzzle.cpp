#include <2021/Day01Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyTwentyOne {
	
	Day01Puzzle::Day01Puzzle() :
		core::PuzzleBase("Sonar Sweep", 2021, 1) {
	}


	void Day01Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day01Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day01Puzzle::fastSolve() {
		auto depths = std::vector<int>();

		for (const auto& s : m_InputLines) {
			depths.push_back(std::stoi(s));
		}

		int currentDepth = depths.front();
		int part1 = 0;
		for (unsigned i = 1; i < depths.size(); ++i) {
			if (depths[i] > currentDepth) {
				part1++;
			}
			currentDepth = depths[i];
		}

		int part2 = 0;
		int currentDepth2 = depths[0] + depths[1] + depths[2];

		for (unsigned i = 1; i + 2u < depths.size(); ++i) {
			if (depths[i + 0u] + depths[i + 1u] + depths[i + 2u] > currentDepth2) {
				part2++;
			}
			currentDepth2 = depths[i + 0u] + depths[i + 1u] + depths[i + 2u];
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
