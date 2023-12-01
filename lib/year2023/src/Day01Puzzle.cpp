#include <2023/Day01Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <string>
#include <numeric>
#include <cassert>

namespace TwentyTwentyThree {
	
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

		const std::vector<std::string> numbers = {
			"zero",
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
			const auto firstNumeric = l.find_first_of("0123456789");
			const auto lastNumeric = l.find_last_of("0123456789");

			{
				if (firstNumeric != std::numeric_limits<std::size_t>::max() &&
					lastNumeric != std::numeric_limits<std::size_t>::max())
				{
					const auto firstDigit = (long)l[firstNumeric] - (long)'0';
					const auto lastDigit = (long)l[lastNumeric] - (long)'0';

					part1 += firstDigit * 10 + lastDigit;
				}
			}

			std::vector<long> foundNumbers;
			
			for (std::size_t i = 0; i < l.size(); ++i)
			{
				const char c = l[i];
				if ('0' <= c && c <= '9')
				{
					foundNumbers.push_back((long)(c - '0'));
				}
				else
				{
					long index = 0;
					for (const auto& strNum : numbers)
					{
						const auto loc = l.find(strNum, i);
						if (loc == i)
						{
							foundNumbers.push_back(index);
							break;
						}
						index++;
					}
				}
			}

			if (getVerbose())
			{
				std::cout << l << '\n';
				for (const auto& d : foundNumbers)
				{
					std::cout << " " << d;
				}
				std::cout << std::endl;
			}

			part2 += foundNumbers[0] * 10 + foundNumbers.back();
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
