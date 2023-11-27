#include <2023/Day10Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>

namespace TwentyTwentyThree {
	
	Day10Puzzle::Day10Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2023, 10) {
	}


	void Day10Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day10Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day10Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
