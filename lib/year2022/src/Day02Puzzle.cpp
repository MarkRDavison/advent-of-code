#include <2022/Day02Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_map>

#define ROCK_THEM 'A'
#define PAPER_THEM 'B'
#define SCISSORS_THEM 'C'

#define ROCK_YOU 'X'
#define PAPER_YOU 'Y'
#define SCISSORS_YOU 'Z'

#define RESULT_LOSE 'X'
#define RESULT_DRAW 'Y'
#define RESULT_WIN 'Z'


namespace TwentyTwentyTwo {
	
	Day02Puzzle::Day02Puzzle() :
		core::PuzzleBase("Rock Paper Scissors", 2022, 2) {
	}


	void Day02Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day02Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	int scoreRound(char _them, char _you)
	{
		int roundScore = (int)(_you - ROCK_YOU) + 1;
		int result = 0;

		if (
			_them == ROCK_THEM && _you == ROCK_YOU ||
			_them == PAPER_THEM && _you == PAPER_YOU ||
			_them == SCISSORS_THEM && _you == SCISSORS_YOU
		)
		{
			result = 3;
		}
		else if (
			_them == ROCK_THEM && _you == PAPER_YOU ||
			_them == PAPER_THEM && _you == SCISSORS_YOU ||
			_them == SCISSORS_THEM && _you == ROCK_YOU)
		{
			result = 6;
		}

		return roundScore + result;
	}

	std::pair<std::string, std::string> Day02Puzzle::fastSolve() {


		const std::unordered_map<char, std::unordered_map<char, char>> themOutcomeYouMap
		{
			{ ROCK_THEM,
				{
					{ RESULT_LOSE, SCISSORS_YOU },
					{ RESULT_DRAW, ROCK_YOU },
					{ RESULT_WIN,  PAPER_YOU }
				}
			},

			{ PAPER_THEM,
				{
					{ RESULT_LOSE, ROCK_YOU },
					{ RESULT_DRAW, PAPER_YOU },
					{ RESULT_WIN, SCISSORS_YOU }
				}
			},

			{ SCISSORS_THEM,
				{
					{ RESULT_LOSE, PAPER_YOU },
					{ RESULT_DRAW, SCISSORS_YOU },
					{ RESULT_WIN, ROCK_YOU }
				}
			}
		};

		int part1 = 0;
		int part2 = 0;

		for (const auto& l : m_InputLines)
		{
			const char you = themOutcomeYouMap.at(l[0]).at(l[2]);
			part1 += scoreRound(l[0], l[2]);
			part2 += scoreRound(l[0], you);
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
