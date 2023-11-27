#include <2023/Day02Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>

namespace TwentyTwentyThree {
	
	Day02Puzzle::Day02Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2023, 2) {
	}


	void Day02Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day02Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day02Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
