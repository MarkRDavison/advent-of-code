#ifndef INCLUDED_ADVENT_OF_CODE_2018_DAY_14_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_DAY_14_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyEighteen {

	typedef long long ChocolateChartNumber;

	struct Elf
	{
		std::size_t recipie;
	};
	
	class Day14Puzzle : public core::PuzzleBase {
	public:
		Day14Puzzle();
		~Day14Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static void processChocolateRecipieInfo(std::vector<Elf>& elves, std::vector<ChocolateChartNumber>& recipies);

		static std::string solvePart1(ChocolateChartNumber input);
		static std::string solvePart2(std::string inputStr, bool verbose);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2018_DAY_14_PUZZLE_HPP_