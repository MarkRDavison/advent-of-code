#include <2021/Day07Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <algorithm>
#include <limits>
#include <cmath>

namespace TwentyTwentyOne {
	
	Day07Puzzle::Day07Puzzle() :
		core::PuzzleBase("The Treachery of Whales", 2021, 7) {
	}


	void Day07Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByLines(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0])));
	}

	void Day07Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day07Puzzle::fastSolve() {
		std::map<long, int> crabLocations;
		for (const auto& s : ze::StringExtensions::splitStringByDelimeter(m_InputLines[0], ",")) {
			crabLocations[std::stoi(s)] += 1;
		}
		const long min = (*std::min_element(crabLocations.begin(), crabLocations.end(), [](const auto& _lhs, const auto& _rhs) -> bool {
			return _lhs.first < _rhs.first;
		})).first;
		const long max = (*std::max_element(crabLocations.begin(), crabLocations.end(), [](const auto& _lhs, const auto& _rhs) -> bool {
			return _lhs.first < _rhs.first;
		})).first;

		long part1MinFuel = std::numeric_limits<long>::max();
		long part2MinFuel = std::numeric_limits<long>::max();

		for (long i = min; i <= max; ++i) {
			const auto fuel1 = solveForPosition(crabLocations, i, true);
			if (fuel1 < part1MinFuel) {
				part1MinFuel = fuel1;
			}
			const auto fuel2 = solveForPosition(crabLocations, i, false);
			if (fuel2 < part2MinFuel) {
				part2MinFuel = fuel2;
			}
		}

		return { std::to_string(part1MinFuel), std::to_string(part2MinFuel) };
	}

	long Day07Puzzle::solveForPosition(const std::map<long, int>& _crabLocations, long _position, bool _part1) {
		const long min = (*std::min_element(_crabLocations.begin(), _crabLocations.end(), 
			[](const auto& _lhs, const auto& _rhs) -> bool {
				return _lhs.first < _rhs.first;
			})).first;

		const long max = (*std::max_element(_crabLocations.begin(), _crabLocations.end(), 
			[](const auto& _lhs, const auto& _rhs) -> bool {
				return _lhs.first < _rhs.first;
			})).first;

		long fuel = 0;

		for (const auto& [loc, number] : _crabLocations) {
			const long diff = std::abs(_position - loc);
			if (_part1) {
				fuel += diff * number;
			}
			else {
				fuel += (diff * diff + diff) / 2 * number;
			}
		}

		return fuel;
	}
}
