#include <2017/Day01Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>

namespace TwentySeventeen {
	
	Day01Puzzle::Day01Puzzle() :
		core::PuzzleBase("Inverse Captcha", 2017, 1) {

	}
	Day01Puzzle::~Day01Puzzle() {

	}


	void Day01Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day01Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day01Puzzle::fastSolve() {

		long part1 = 0;
		long part2 = 0;

		std::size_t length = m_InputLines[0].size();
		std::size_t jump = length / 2;

		for (std::size_t i = 0; i < length; i += 1) {
			const auto val1 = m_InputLines[0][i];
			const auto val2_1 = m_InputLines[0][(i + 1) % length];
			const auto val2_2 = m_InputLines[0][(i + jump) % length];

			if (val1 == val2_1) {
				part1 += (long)(val1 - '0');
			}
			if (val1 == val2_2) {
				part2 += (long)(val1 - '0');
			}
		}


		return { std::to_string(part1), std::to_string(part2) };
	}
}
