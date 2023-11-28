#include <2017/Day15Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <bitset>
namespace TwentySeventeen {
	
	Day15Puzzle::Day15Puzzle() :
		core::PuzzleBase("Dueling Generators", 2017, 15) {

	}
	Day15Puzzle::~Day15Puzzle() {

	}


	void Day15Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day15Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}


	std::pair<std::string, std::string> Day15Puzzle::fastSolve() {

		const auto& aParts = StringExtensions::splitStringByDelimeter(m_InputLines[0], " "); 
		const auto& bParts = StringExtensions::splitStringByDelimeter(m_InputLines[1], " ");

		const auto aStart = std::stoull(aParts.back());
		const auto bStart = std::stoull(bParts.back());

		const unsigned long long aFactor = 16807;
		const unsigned long long bFactor = 48271;

		unsigned long long aValue = aStart;
		unsigned long long bValue = bStart;

		int part1 = 0;
		int part2 = 0;

		for (std::size_t i = 0; i < 40000000; ++i) {
			unsigned long long aNext = (aValue * aFactor) % 2147483647;
			unsigned long long bNext = (bValue * bFactor) % 2147483647;
		
			std::bitset<16> aBin(aNext);
			std::bitset<16> bBin(bNext);
		
			if (aBin == bBin) {
				part1++;
			}
		
			aValue = aNext;
			bValue = bNext;
		}

		aValue = aStart;
		bValue = bStart;
		for (std::size_t i = 0; i < 5000000; ++i) {
			unsigned long long aNext;
			unsigned long long bNext;

			do {
				aNext = (aValue * aFactor) % 2147483647;
				aValue = aNext;
			} while (aNext % 4 != 0);

			do {
				bNext = (bValue * bFactor) % 2147483647;
				bValue = bNext;
			} while (bNext % 8 != 0);

			std::bitset<16> aBin(aNext);
			std::bitset<16> bBin(bNext);

			if (aBin == bBin) {
				part2++;
			}

		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
