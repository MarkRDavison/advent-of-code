#include <2019/Day08Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyNineteen {
	
	Day08Puzzle::Day08Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2019, 8) {

	}
	Day08Puzzle::~Day08Puzzle() {

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
