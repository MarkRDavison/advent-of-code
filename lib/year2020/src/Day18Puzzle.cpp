#include <2020/Day18Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <algorithm>
#include <cassert>

namespace TwentyTwenty {
	
	Day18Puzzle::Day18Puzzle() :
		core::PuzzleBase("FILL ME IN !?!?!!?!?!", 2020, 18) {
	}


	void Day18Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day18Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day18Puzzle::fastSolve() {
		const auto& parsed = Day18Puzzle::parse(m_InputLines);

		const auto part1 = Day18Puzzle::doPart1(parsed);
		const auto part2 = Day18Puzzle::doPart2(parsed);

		return { part1, part2 };
	}

	std::vector<Day18Struct> Day18Puzzle::parse(const std::vector<std::string>& _inputLines) {
		std::vector<Day18Struct> parsed;
		std::transform(_inputLines.begin(), _inputLines.end(), std::back_inserter(parsed), translate);
		return parsed;
	}
	Day18Struct Day18Puzzle::translate(const std::string& _str) {
		Day18Struct s{};

		for (const auto c : _str) {
			Day18Struct::TokenType type;
			Day18Number number = -1;
			if (c == '*') {
				type = Day18Struct::TokenType::Times;
			}
			else if (c == '+') {
				type = Day18Struct::TokenType::Plus;
			}
			else if (c == '(') {
				type = Day18Struct::TokenType::OpenBracket;
			}
			else if (c == ')') {
				type = Day18Struct::TokenType::CloseBracket;
			}
			else if ('0' <= c && c <= '9') {
				type = Day18Struct::TokenType::Digit;
				number = static_cast<long>(c - '0');
			}
			else {
				assert(c == ' ');
				continue;
			}

			s.parsed.emplace_back(type, number);
		}

		return s;
	}

	Day18Number recurser(const Day18Struct::ParsedTokens& _tokens, unsigned _start, unsigned _end) {

		Day18Number total = 0;
		Day18Struct::TokenType previousToken = Day18Struct::TokenType::NotApplicable;


		for (unsigned i = _start; i < _end; ++i) {
			if (_tokens[i].first == Day18Struct::TokenType::Digit) {

			}
		}

		return -1;
	}

	std::string Day18Puzzle::doPart1(const std::vector<Day18Struct>& _parsed) {
		Day18Number answer = 0;

		for (const auto& p : _parsed) {
			answer += recurser(p.parsed, 0, p.parsed.size());
		}

		return std::to_string(answer);
	}
	std::string Day18Puzzle::doPart2(const std::vector<Day18Struct>& _parsed) {
		return "";
	}
}
