#include <2019/Day07Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyNineteen {
	
	Day07Puzzle::Day07Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2019, 7) {

	}
	Day07Puzzle::~Day07Puzzle() {

	}


	void Day07Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day07Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day07Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
