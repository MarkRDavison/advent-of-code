#include <2023/Day25Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyTwentyThree {
	
	Day25Puzzle::Day25Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2023, 25) {
	}


	void Day25Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day25Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day25Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
