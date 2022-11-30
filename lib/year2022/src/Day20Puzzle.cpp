#include <2022/Day20Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>

namespace TwentyTwentyTwo {
	
	Day20Puzzle::Day20Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2022, 20) {
	}


	void Day20Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day20Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day20Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
