#include <2021/Day06Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyTwentyOne {
	
	Day06Puzzle::Day06Puzzle() :
		core::PuzzleBase("Lanternfish", 2021, 6) {
	}


	void Day06Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day06Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	LanternFishNumber solveForIterations(unsigned _iterations, std::unordered_map<LanternFishNumber, LanternFishNumber> _lanternFish) {
		LanternFishNumber answer = 0;

		std::unordered_map<LanternFishNumber, LanternFishNumber> lanternFish(_lanternFish);

		for (unsigned i = 0; i < _iterations; ++i) {
			lanternFish = Day06Puzzle::iterateLanternFish(lanternFish);
		}

		for (const auto& [timer, amount] : lanternFish) {
			answer += amount;
		}

		return answer;
	}

	std::pair<std::string, std::string> Day06Puzzle::fastSolve() {
		std::unordered_map<LanternFishNumber, LanternFishNumber> lanternFish;
		for (const auto& s : StringExtensions::splitStringByDelimeter(m_InputLines[0], ",")) {
			lanternFish[std::stoi(s)] += 1;
		}

		const auto part1 = solveForIterations(80, lanternFish);
		const auto part2 = solveForIterations(256, lanternFish);

		return { std::to_string(part1), std::to_string(part2) };
	}

	std::unordered_map<LanternFishNumber, LanternFishNumber> Day06Puzzle::iterateLanternFish(const std::unordered_map<LanternFishNumber, LanternFishNumber>& _lanternFish) {
		std::unordered_map<LanternFishNumber, LanternFishNumber> newLanternFish;

		LanternFishNumber spawned = 0;
		for (const auto& [timer, amount] : _lanternFish) {
			if (timer > 0) {
				newLanternFish[timer - 1] = amount;
			} else {
				spawned += amount;
			}
		}

		if (spawned > 0) {
			newLanternFish[6] += spawned;
			newLanternFish[8] += spawned;
		}

		return newLanternFish;
	}
}
