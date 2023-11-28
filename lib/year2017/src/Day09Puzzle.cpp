#include <2017/Day09Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <cassert>

namespace TwentySeventeen {
	
	Day09Puzzle::Day09Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2017, 9) {

	}
	Day09Puzzle::~Day09Puzzle() {

	}


	void Day09Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day09Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day09Puzzle::fastSolve() {
		const auto [part1, part2] = removeGarbage(m_InputLines[0]);
		return { std::to_string(part1), std::to_string(part2) };
	}

	std::pair<std::size_t, std::size_t> Day09Puzzle::removeGarbage(const std::string& _input) {
		std::size_t totalScore = 0;
		std::size_t f = 0;
		bool inGroup = false;
		std::size_t d = 1;

		for (std::size_t i = 0; i < _input.size(); ++i) {
			const char curr = _input[i];

			if (curr == '!') {
				i++;
			}
			else if (curr == '>') {
				inGroup = false;
			}
			else if (inGroup) {
				f++;
			}
			else if (curr == '{' && !inGroup) { 
				totalScore += d;
				d++;
			}
			else if (curr == '}' && !inGroup) {
				d--;
			}
			else if (curr == '<') {
				inGroup = true;
			}
		}

		return { totalScore, f };
	}
}
