#include <2023/Day21Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyTwentyThree {
	
	Day21Puzzle::Day21Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2023, 21) {
	}


	void Day21Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day21Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day21Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
