#include <2023/Day14Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>

namespace TwentyTwentyThree {
	
	Day14Puzzle::Day14Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2023, 14) {
	}


	void Day14Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day14Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day14Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
