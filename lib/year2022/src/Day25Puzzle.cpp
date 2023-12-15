#include <2022/Day25Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <cassert>

#define CHARS std::string("=-012")
#define NUMBER_BASE 5
#define ZERO_INDEX 2

namespace TwentyTwentyTwo {


	
	Day25Puzzle::Day25Puzzle() :
		core::PuzzleBase("Full of Hot Air", 2022, 25) {
	}


	void Day25Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day25Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	long long Day25Puzzle::SnafuToDecimal(const std::string& snafu)
	{
		long long decimal = 0;

		for (const char c : snafu)
		{
			decimal *= NUMBER_BASE;
			decimal += CHARS.find(c) - ZERO_INDEX;
		}

		return decimal;
	}
	std::string Day25Puzzle::DecimalToSnafu(long long decimal)
	{
		std::string snafu;

		while (decimal != 0)
		{
			long long indexInSnafu = (decimal + ZERO_INDEX) % NUMBER_BASE;
			assert(0 <= indexInSnafu && indexInSnafu < NUMBER_BASE);
			snafu += CHARS[indexInSnafu];
			if (indexInSnafu < ZERO_INDEX)
			{
				decimal += NUMBER_BASE;
			}

			decimal /= NUMBER_BASE;
		}


		return std::string(snafu.rbegin(), snafu.rend());
	}

	std::pair<std::string, std::string> Day25Puzzle::fastSolve() {

		long long sum = 0;
		for (const auto& l : m_InputLines) 
		{
			sum += SnafuToDecimal(l);
		}

		return { DecimalToSnafu(sum), "*** Free ***"};
	}
}
