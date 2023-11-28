#include <2023/Day22Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyTwentyThree {
	
	Day22Puzzle::Day22Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2023, 22) {
	}


	void Day22Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day22Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day22Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
