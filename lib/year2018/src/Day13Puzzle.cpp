#include <2018/Day13Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyEighteen {
	
	Day13Puzzle::Day13Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2018, 13) {

	}
	Day13Puzzle::~Day13Puzzle() {

	}


	void Day13Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day13Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day13Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
