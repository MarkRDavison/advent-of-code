#include <2022/Day23Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyTwentyTwo {
	
	Day23Puzzle::Day23Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2022, 23) {
	}


	void Day23Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day23Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day23Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
