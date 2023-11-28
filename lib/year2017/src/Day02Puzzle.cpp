#include <2017/Day02Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <algorithm>

namespace TwentySeventeen {
	
	Day02Puzzle::Day02Puzzle() :
		core::PuzzleBase("Corruption Checksum", 2017, 2) {

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

		int part1 = 0;
		int part2 = 0;

		for (const auto& row : m_InputLines) {
			std::vector<int> rowNumbers;
			for (const auto& number : StringExtensions::splitStringByDelimeter(row, " \t")) {
				rowNumbers.push_back(std::stoi(number));
			}

			const auto max = std::max_element(rowNumbers.begin(), rowNumbers.end());
			const auto min = std::min_element(rowNumbers.begin(), rowNumbers.end());

			for (std::size_t i = 0; i < rowNumbers.size(); ++i) {
				for (std::size_t j = i + 1; j < rowNumbers.size(); ++j) {
					const auto minVal = std::min(rowNumbers[i], rowNumbers[j]);
					const auto maxVal = std::max(rowNumbers[i], rowNumbers[j]);

					if (maxVal % minVal == 0) {
						part2 += maxVal / minVal;
					}
				}
			}

			const auto diff = *max - *min;

			part1 += diff;
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
