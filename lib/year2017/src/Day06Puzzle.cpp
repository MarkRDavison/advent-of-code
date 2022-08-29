#include <2017/Day06Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>

#include <unordered_set>
#include <unordered_map>

namespace TwentySeventeen {
	
	Day06Puzzle::Day06Puzzle() :
		core::PuzzleBase("Memory Reallocation", 2017, 6) {

	}
	Day06Puzzle::~Day06Puzzle() {

	}


	void Day06Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day06Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	static std::string hash(const std::vector<int>& _banks) {
		std::string h;
		for (const auto& i : _banks) {
			h += std::to_string(i) + "-";
		}
		return h;
	}


	std::pair<std::string, std::string> Day06Puzzle::fastSolve() {
		std::vector<int> blocks;

		for (const auto& part : ze::StringExtensions::splitStringByDelimeter(m_InputLines[0], " \t")) {
			blocks.push_back(std::stoi(part));
		}

		auto banks(blocks);
		std::unordered_set<std::string> seen;
		std::unordered_map<std::string, std::size_t> lastOccurence;

		std::size_t iter = 0;
		while (seen.count(hash(banks)) == 0) {
			const auto h = hash(banks);

			seen.insert(h);
			lastOccurence[h] = iter;

			auto maxIndex = std::distance(banks.begin(), std::max_element(banks.begin(), banks.end()));

			const int value = banks[maxIndex];
			banks[maxIndex] = 0;

			for (int i = 0; i < value; ++i) {
				banks[(maxIndex + i + 1) % banks.size()] += 1;
			}

			iter++;
		}

		const auto part1 = seen.size();

		return { std::to_string(part1), std::to_string(iter - lastOccurence[hash(banks)]) };
	}
}
