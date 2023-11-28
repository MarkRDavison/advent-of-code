#include <2021/Day02Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyTwentyOne {
	
	Day02Puzzle::Day02Puzzle() :
		core::PuzzleBase("Dive!", 2021, 2) {
	}


	void Day02Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day02Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day02Puzzle::fastSolve() {

		int horizontal = 0;
		int depth = 0;

		int aim = 0;
		int depth2 = 0;

		for (const auto& i : m_InputLines) {
			const auto& s = StringExtensions::splitStringByDelimeter(i, " ");

			const auto v = std::stoi(s[1]);

			if (s[0] == "forward") {
				horizontal += v;
				depth2 += aim * v;
			} else if (s[0] == "down") {
				depth += v;
				aim += v;
			} else if (s[0] == "up") {
				depth -= v;
				aim -= v;
			}
		}

		return { std::to_string(horizontal * depth), std::to_string(horizontal * depth2) };
	}
}
