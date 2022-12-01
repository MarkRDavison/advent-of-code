#include <2022/Day01Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <algorithm>

namespace TwentyTwentyTwo {
	
	Day01Puzzle::Day01Puzzle() :
		core::PuzzleBase("Calorie Counting", 2022, 1) {
	}


	void Day01Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByLines(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0])));
	}

	void Day01Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day01Puzzle::fastSolve() {

		std::vector<int> data{ 0 };

		for (const auto& l : m_InputLines)
		{
			if (l.empty()) {
				data.emplace_back(0);
				continue;
			}

			data.back() += std::stoi(l);
		}

		std::sort(data.begin(), data.end());
		const auto part1 = data[data.size() - 1];

		const auto part2 = data[data.size() - 1] + data[data.size() - 2]+ data[data.size() - 3];

		return { std::to_string(part1), std::to_string(part2) };
	}
}
