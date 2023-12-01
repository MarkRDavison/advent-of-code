#include <2023/Day01Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <string>
#include <numeric>

namespace TwentyTwentyThree {

	typedef std::pair<long, bool> NumberString;
	
	Day01Puzzle::Day01Puzzle() :
		core::PuzzleBase("Trebuchet?!", 2023, 1) {
	}


	void Day01Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day01Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day01Puzzle::fastSolve() {
		long part1 = 0;
		long part2 = 0;

		constexpr long MAX_LONG = std::numeric_limits<long>::max();

		const std::vector<std::string> numbers = {
			"one",
			"two",
			"three",
			"four",
			"five",
			"six",
			"seven",
			"eight",
			"nine"
		};

		for (const auto& l : m_InputLines)
		{
			std::vector<NumberString> numberStrings;

			for (std::size_t i = 0; i < l.size(); ++i)
			{
				const char c = l[i];
				if ('0' <= c && c <= '9')
				{
					numberStrings.push_back(NumberString((long)(c - '0'), false));
				}
				else
				{
					long index = 0;
					for (const auto& strNum : numbers)
					{
						const auto loc = l.find(strNum, i);
						if (loc == i)
						{
							numberStrings.push_back(NumberString(index+1, true));
							break;
						}
						index++;
					}
				}
			}

			long part1First = MAX_LONG;
			long part2First = MAX_LONG;
			long part1Last = MAX_LONG;
			long part2Last = MAX_LONG;

			for (const auto& [number, isString] : numberStrings)
			{
				if (part1First == MAX_LONG && !isString)
				{
					part1First = number;
				}
				if (part2First == MAX_LONG)
				{
					part2First = number;
				}

				if (part1First != MAX_LONG && part2First != MAX_LONG)
				{
					break;
				}
			}

			std::reverse(numberStrings.begin(), numberStrings.end());

			for (const auto& [number, isString] : numberStrings)
			{
				if (part1Last == MAX_LONG && !isString)
				{
					part1Last = number;
				}
				if (part2Last == MAX_LONG)
				{
					part2Last = number;
				}

				if (part1Last != MAX_LONG && part2Last != MAX_LONG)
				{
					break;
				}
			}

			part1 += part1First * 10 + part1Last;
			part2 += part2First * 10 + part2Last;
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
