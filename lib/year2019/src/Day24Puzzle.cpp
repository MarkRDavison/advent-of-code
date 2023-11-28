#include <2019/Day24Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyNineteen {
	
	Day24Puzzle::Day24Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2019, 24) {

	}
	Day24Puzzle::~Day24Puzzle() {

	}


	void Day24Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day24Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day24Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
