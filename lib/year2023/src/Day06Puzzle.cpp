#include <2023/Day06Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyTwentyThree {
	
	Day06Puzzle::Day06Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2023, 6) {
	}


	void Day06Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day06Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day06Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
