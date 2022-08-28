#include <2017/Day05Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>

namespace TwentySeventeen {
	
	Day05Puzzle::Day05Puzzle() :
		core::PuzzleBase("A Maze of Twisty Trampolines, All Alike", 2017, 5) {

	}
	Day05Puzzle::~Day05Puzzle() {

	}


	void Day05Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day05Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day05Puzzle::fastSolve() {
		std::vector<int> values;
		for (const auto& i : m_InputLines) {
			const int val = std::stoi(i);
			values.push_back(val);
		}

		int part1 = 0;
		int pc = 0;

		while (pc >= 0 && pc < values.size()) {
			auto& val = values[pc];

			pc += val;
			val += 1;

			part1++;
		}

		int part2 = 0;
		pc = 0;
		values.clear();
		for (const auto& i : m_InputLines) {
			const int val = std::stoi(i);
			values.push_back(val);
		}

		while (pc >= 0 && pc < values.size()) {
			auto& val = values[pc];

			pc += val;
			if (val >= 3) {
				val -= 1;
			}
			else {
				val += 1;
			}

			part2++;
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
