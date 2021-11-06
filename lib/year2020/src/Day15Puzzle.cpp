#include <2020/Day15Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <algorithm>
#include <unordered_map>

namespace TwentyTwenty {
	
	Day15Puzzle::Day15Puzzle() :
		core::PuzzleBase("Untitled Puzzle", 2020, 15) {
	}


	void Day15Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day15Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day15Puzzle::fastSolve() {
		const auto& parsed = Day15Puzzle::parse(m_InputLines);

		const auto part1 = Day15Puzzle::doPart(parsed, 2020);
		const auto part2 = Day15Puzzle::doPart(parsed, 30000000);

		return { part1, part2 };
	}

	std::vector<Day15Number> Day15Puzzle::parse(const std::vector<std::string>& _inputLines) {
		std::vector<Day15Number> parsed;
		const auto& parts = ze::StringExtensions::splitStringByDelimeter(_inputLines[0], ",");
		std::transform(parts.begin(), parts.end(), std::back_inserter(parsed),
			[](const std::string& _str) -> Day15Number {
				return std::stoll(_str);
			});
		return parsed;
	}

	std::string Day15Puzzle::doPart(const std::vector<Day15Number>& _parsed, Day15Number _numberIndex) {
		struct NumberLastSpoken {

			NumberLastSpoken() : NumberLastSpoken(1, 1) {}
			NumberLastSpoken(Day15Number _mostRecent, Day15Number _secondMostRecent) :
				mostRecent(_mostRecent), secondMostRecent(_secondMostRecent) {

			}

			bool operator==(const NumberLastSpoken& _other) {
				return mostRecent == _other.mostRecent && secondMostRecent == _other.secondMostRecent;
			}

			Day15Number mostRecent;
			Day15Number secondMostRecent;
		};
		Day15Number lastNumber = _parsed.back();
		std::unordered_map<Day15Number, NumberLastSpoken> numbersLastSpokenTurns;
		for (unsigned i = 0; i < _parsed.size(); ++i) {
			numbersLastSpokenTurns[_parsed[i]] = NumberLastSpoken(i + 1, i + 1);
		}

		for (Day15Number i = _parsed.size() + 1; i <= _numberIndex; ++i) {
			auto& lastNumberSpokenInfo = numbersLastSpokenTurns[lastNumber];

			const auto newNumber = lastNumberSpokenInfo.mostRecent - lastNumberSpokenInfo.secondMostRecent;

			if (numbersLastSpokenTurns.find(newNumber) == numbersLastSpokenTurns.end()) {
				numbersLastSpokenTurns[newNumber] = NumberLastSpoken(i, i);
			}
			else {
				auto& last = numbersLastSpokenTurns[newNumber];
				last.secondMostRecent = last.mostRecent;
				last.mostRecent = i;
			}
			lastNumber = newNumber;
		}


		return std::to_string(lastNumber);
	}
}
