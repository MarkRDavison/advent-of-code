#include <2021/Day03Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <unordered_map>
#include <algorithm>

namespace TwentyTwentyOne {
	
	Day03Puzzle::Day03Puzzle() :
		core::PuzzleBase("Binary Diagnostic", 2021, 3) {
	}


	void Day03Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day03Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::string calculatePart1(const std::vector<std::string>& _inputLines) {
		std::unordered_map<int, std::pair<int, int>> bitOccurences;

		for (const auto& s : _inputLines) {
			int index = 0;
			for (const auto& c : s) {
				if (c == '0') {
					bitOccurences[index].first++;
				} else {
					bitOccurences[index].second++;
				}
				index++;
			}
		}

		std::string gamma;
		std::string epsilon;

		for (int i = 0; i < (int)bitOccurences.size(); ++i) {
			if (bitOccurences[i].first > bitOccurences[i].second) {
				gamma += '0';
				epsilon += '1';
			} else {
				gamma += '1';
				epsilon += '0';
			}
		}

		int gammaInt = std::stoi(gamma, nullptr, 2);
		int epsilonInt = std::stoi(epsilon, nullptr, 2);

		return std::to_string(gammaInt * epsilonInt);
	}

	std::vector<std::string> removeBadNumbers(const std::vector<std::string>& _inputLines, unsigned _index, bool _mostCommon) {
		std::vector<std::string> outputLines;

		int count0 = 0;
		int count1 = 0;

		for (const auto& i : _inputLines) {
			if (i[_index] == '0') {
				count0++;
			} else {
				count1++;
			}
		}

		char indexC = count0 > count1 ? '0' : '1';
		if (!_mostCommon) {
			indexC = indexC == '0' ? '1' : '0';
		}

		std::copy_if(_inputLines.begin(), _inputLines.end(), std::back_inserter(outputLines), [indexC, _index, _mostCommon](const std::string& line) {
			return indexC == line[_index];
		});

		return outputLines;
	}


	std::string calculatePart2(const std::vector<std::string>& _inputLines) {

		auto o2 = std::vector<std::string>(_inputLines);

		for (unsigned i = 0; i < o2.front().size(); ++i) {
			o2 = removeBadNumbers(o2, i, true);
			if (o2.size() == 1) {
				break;
			}
		}


		auto co2 = std::vector<std::string>(_inputLines);

		for (unsigned i = 0; i < co2.front().size(); ++i) {
			co2 = removeBadNumbers(co2, i, false);
			if (co2.size() == 1) {
				break;
			}
		}

		int o2Int = std::stoi(o2[0], nullptr, 2);
		int co2Int = std::stoi(co2[0], nullptr, 2);

		return std::to_string(o2Int * co2Int);
	}

	std::pair<std::string, std::string> Day03Puzzle::fastSolve() {
		return { calculatePart1(m_InputLines), calculatePart2(m_InputLines) };
	}
}
