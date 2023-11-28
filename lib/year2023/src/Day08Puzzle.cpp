#include <2023/Day08Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyTwentyThree {
	
	Day08Puzzle::Day08Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2023, 8) {
	}


	void Day08Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day08Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day08Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
