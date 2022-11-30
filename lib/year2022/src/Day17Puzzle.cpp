#include <2022/Day17Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>

namespace TwentyTwentyTwo {
	
	Day17Puzzle::Day17Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2022, 17) {
	}


	void Day17Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day17Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day17Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
