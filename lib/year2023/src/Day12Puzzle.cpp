#include <2023/Day12Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyTwentyThree {
	
	Day12Puzzle::Day12Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2023, 12) {
	}


	void Day12Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day12Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day12Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
