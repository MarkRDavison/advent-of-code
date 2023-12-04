#include <2023/Day04Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_set>
#include <unordered_map>

namespace TwentyTwentyThree {
	
	Day04Puzzle::Day04Puzzle() :
		core::PuzzleBase("Scratchcards", 2023, 4) {
	}


	void Day04Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day04Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	typedef long long ScratchCardNumber;
	typedef std::vector<ScratchCardNumber> ScratchCardNumberVector;
	typedef std::unordered_set<ScratchCardNumber> ScratchCardNumberSet;
	typedef std::unordered_map<std::size_t, ScratchCardNumber> ScratchCardDuplicateMap;

	struct ScratchCard
	{
		ScratchCardNumber cardNumber;
		ScratchCardNumberVector winningNumbers;
		ScratchCardNumberVector numbers;
		ScratchCardNumberSet winningNumbersSet;
		ScratchCardNumberSet numbersSet;
	};

	std::pair<std::string, std::string> Day04Puzzle::fastSolve() {
		std::vector< ScratchCard> cards;
		ScratchCardDuplicateMap duplicates;


		for (const auto& l : m_InputLines)
		{
			auto& c = cards.emplace_back();

			const auto& parts = StringExtensions::splitStringByDelimeter(l, " :");

			c.cardNumber = (ScratchCardNumber)std::stoll(parts[1]);
			duplicates[c.cardNumber] = 1;

			std::size_t i = 2;
			for (i = 2; ; ++i)
			{
				if (parts[i] == "|")
				{
					i++;
					break;
				}
				c.winningNumbers.push_back((ScratchCardNumber)std::stoll(parts[i]));
				c.winningNumbersSet.emplace((ScratchCardNumber)std::stoll(parts[i]));
			}

			for (; i < parts.size(); ++i)
			{
				c.numbers.push_back((ScratchCardNumber)std::stoll(parts[i]));
				c.numbersSet.emplace((ScratchCardNumber)std::stoll(parts[i]));
			}
		}

		ScratchCardNumber part1 = 0;
		ScratchCardNumber part2 = 0;


		for (const auto& c : cards)
		{
			ScratchCardNumber winningNumbers = 0;
			ScratchCardNumber currentCardScore = 1;
			for (const auto number : c.numbersSet)
			{
				if (c.winningNumbersSet.contains(number))
				{
					winningNumbers++;
					if (winningNumbers > 1)
					{
						currentCardScore *= 2;
					}
				}
			}

			if (winningNumbers > 0)
			{
				for (ScratchCardNumber i = c.cardNumber + 1; i < c.cardNumber + 1 + winningNumbers; ++i) 
				{
					duplicates[i] += duplicates[c.cardNumber];
				}
				part1 += currentCardScore;
			}
		}

		for (const auto& [cardNumber, amount] : duplicates)
		{
			part2 += amount;
		}

		return { std::to_string(part1) , std::to_string(part2) };
	}
}
