#include <2022/Day16Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>

namespace TwentyTwentyTwo {
	
	Day16Puzzle::Day16Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2022, 16) {
	}


	void Day16Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day16Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day16Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
