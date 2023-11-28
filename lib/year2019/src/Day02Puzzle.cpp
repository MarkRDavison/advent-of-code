#include <2019/Day02Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyNineteen {
	
	Day02Puzzle::Day02Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2019, 2) {

	}
	Day02Puzzle::~Day02Puzzle() {

	}


	void Day02Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day02Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day02Puzzle::fastSolve() {
		return { "Part 1", "Part 2" };
	}
}
