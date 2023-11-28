#include <2020/Day19Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cassert>
#include <numeric>
#include <limits>

namespace TwentyTwenty {

	Day19Puzzle::Day19Puzzle() :
		core::PuzzleBase("Monster Messages", 2020, 19) {
	}


	void Day19Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByLines(StringExtensions::loadFileToString(_initialisationInfo.parameters[0])));
	}

	void Day19Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day19Puzzle::fastSolve() {
		const auto& parsed = Day19Puzzle::parse(m_InputLines);

		const auto part1 = Day19Puzzle::doPart1(parsed);
		const auto part2 = Day19Puzzle::doPart2(parsed);

		return { part1, part2 };
	}

	Day19Struct Day19Puzzle::parse(const std::vector<std::string>& _inputLines) {
		Day19Struct parsed;

		unsigned i = 0;
		for (; !_inputLines[i].empty(); ++i) {
			const auto& parts = StringExtensions::splitStringByDelimeter(_inputLines[i], ": ");
			const long ruleId = std::stol(parts[0]);
			auto& rule = parsed.rules[ruleId];

			if (parts[1][0] == '"') {
				// we have a single character
				rule.character = parts[1][1];
				assert('a' <= rule.character && rule.character <= 'z');
				continue;
			}

			rule.subrules.emplace_back();
			for (unsigned j = 1; j < parts.size(); ++j) {
				if (parts[j] == "|") {
					rule.subrules.emplace_back();
					continue;
				}
				rule.subrules.back().ruleIds.push_back(std::stoul(parts[j]));
			}
		}

		assert(_inputLines[i].empty());

		for (i = i + 1; i < _inputLines.size(); ++i) {
			auto& message = parsed.messages.emplace_back();
			message.message = _inputLines[i];
		}

		return parsed;
	}

	unsigned recurse(const Day19Struct& _parsed, const std::string& _message, unsigned _start, unsigned _ruleId) {
		const auto& rule = _parsed.rules.at(_ruleId);

		if (_ruleId == 8) {

		}
		else if (_ruleId == 11) {

		}
		else if (rule.character == '?') {
			// Sub Rule
			for (const auto& subRule : rule.subrules) {
				auto subStart = _start;
				bool valid = true;
				for (const auto& subRuleId : subRule.ruleIds) {
					auto subAnswer = recurse(_parsed, _message, subStart, subRuleId);
					if (subAnswer == std::numeric_limits<unsigned>::max()) {
						valid = false;
						break;
					}
					subStart = subAnswer;
				}
				if (valid) {
					return subStart;
				}
			}
		}
		else {
			// Character Rule
			if (_message[_start] == rule.character) {
				return _start + 1;
			}
		}

		return std::numeric_limits<unsigned>::max();
	}

	bool Day19Puzzle::matchRule(const Day19Struct& _parsed, unsigned _ruleId, const std::string& _message) {
		const auto last = recurse(_parsed, _message, 0, _ruleId);
		return last == _message.size();
	}

	std::string Day19Puzzle::doPart1(const Day19Struct& _parsed) {
		int count = 0;

		for (const auto& m : _parsed.messages) {
			if (matchRule(_parsed, 0, m.message)) {
				count++;
			}
		}

		return std::to_string(count);
	}
	std::string Day19Puzzle::doPart2(const Day19Struct& _parsed) {
		return doPart1(transformPart1ToPart2(_parsed));
	}
	Day19Struct Day19Puzzle::transformPart1ToPart2(const Day19Struct& _parsed) {
		Day19Struct _parsedPart2(_parsed);

		{
			auto& rule = _parsedPart2.rules[8];
			rule.character = '?';
			rule.subrules.clear();
			{
				auto& subRule = rule.subrules.emplace_back();
				subRule.ruleIds = { 42 };
			}
			{
				auto& subRule = rule.subrules.emplace_back();
				subRule.ruleIds = { 42, 8 };
			}
		}

		{
			auto& rule = _parsedPart2.rules[11];
			rule.character = '?';
			rule.subrules.clear();
			{
				auto& subRule = rule.subrules.emplace_back();
				subRule.ruleIds = { 42, 31 };
			}
			{
				auto& subRule = rule.subrules.emplace_back();
				subRule.ruleIds = { 42, 11, 31 };
			}
		}

		return _parsedPart2;
	}
}
