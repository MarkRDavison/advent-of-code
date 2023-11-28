#include <2023/Day20Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyTwentyThree {
	
	Day20Puzzle::Day20Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2023, 20) {
	}


	void Day20Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day20Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day20Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
