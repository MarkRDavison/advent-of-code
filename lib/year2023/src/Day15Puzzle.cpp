#include <2023/Day15Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyTwentyThree {
	
	Day15Puzzle::Day15Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2023, 15) {
	}


	void Day15Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day15Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day15Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
