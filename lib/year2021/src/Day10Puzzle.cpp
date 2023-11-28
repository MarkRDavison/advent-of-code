#include <2021/Day10Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_map>
#include <algorithm>
#include <cassert>

namespace TwentyTwentyOne {
	
	Day10Puzzle::Day10Puzzle() :
		core::PuzzleBase("Syntax Scoring", 2021, 10) {
	}


	void Day10Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day10Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day10Puzzle::fastSolve() {
		ScoreNumber part1 = 0;
		std::vector<ScoreNumber> completionScores;

		for (const auto& chunk : m_InputLines) {
			const auto result = isCorrupt(chunk);
			if (result.corrupt) {
				part1 += result.score;
			}
			else if (result.incomplete) {
				const auto completionResult = complete(result, chunk);
				completionScores.push_back(completionResult.score);
			}
		}

		std::sort(completionScores.begin(), completionScores.end());

		assert(((completionScores.size() - 1) % 2) == 0);

		const auto index = (completionScores.size() - 1) / 2;

		return { std::to_string(part1), std::to_string(completionScores[index]) };
	}

	bool isOpenChar(char _c) {
		return
			_c == '[' ||
			_c == '(' ||
			_c == '{' ||
			_c == '<';
	}
	bool isCloseChar(char _c) {
		return
			_c == ']' ||
			_c == ')' ||
			_c == '}' ||
			_c == '>';
	}

	char getOpenCharForCloseChar(char _closeChar) {
		switch (_closeChar) {
		case ']':
			return '[';
		case ')':
			return '(';
		case '}':
			return '{';
		case '>':
			return '<';
		}

		throw std::runtime_error("Invalid close char");
	}

	long getCompletionScore(char _openChar) {
		switch (_openChar) {
		case ']':
			return 2;
		case ')':
			return 1;
		case '}':
			return 3;
		case '>':
			return 4;
		}

		throw std::runtime_error("Invalid close char");
	}

	ScoreNumber getCorruptionScore(char _invalidCloseChar) {
		switch (_invalidCloseChar) {
		case ']':
			return 57;
		case ')':
			return 3;
		case '}':
			return 1197;
		case '>':
			return 25137;
		}

		throw std::runtime_error("Invalid close char");
	}

	CorruptionResult Day10Puzzle::isCorrupt(const std::string& _chunk) {
		std::stack<char> openStack;

		for (const auto& c : _chunk) {
			if (isOpenChar(c)) {
				openStack.push(c);
			}
			else {
				const char top = openStack.top();
				const char topExpected = getOpenCharForCloseChar(c);
				if (top != topExpected) {
					CorruptionResult res;
					res.corrupt = true;
					res.score = getCorruptionScore(c);
					return res;
				}
				openStack.pop();
			}
		}
		CorruptionResult res;
		res.corrupt = false;
		res.incomplete = !openStack.empty();
		res.openStack = openStack;
		return res;
	}

	CompletionResult Day10Puzzle::complete(CorruptionResult _corruption, const std::string& _chunk) {
		CompletionResult res{};
		std::string extra;
		const std::unordered_map<char, char> openToClose = {
			{'[', ']'},
			{'<', '>'},
			{'(', ')'},
			{'{', '}'},
		};
		while (!_corruption.openStack.empty()) {
			const char c = _corruption.openStack.top();
			_corruption.openStack.pop();
			extra += openToClose.at(c);
		}
		res.complete = _chunk + extra;
		res.score = 0;

		for (const auto& c : extra) {
			res.score *= 5;
			res.score += getCompletionScore(c);
		}

		return res;
	}
}
