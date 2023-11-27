#include <2023/Day13Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>

namespace TwentyTwentyThree {
	
	Day13Puzzle::Day13Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2023, 13) {
	}


	void Day13Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day13Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day13Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
