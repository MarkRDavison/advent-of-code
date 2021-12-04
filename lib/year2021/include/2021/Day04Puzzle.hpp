#ifndef INCLUDED_ADVENT_OF_CODE_2021_DAY_04_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2021_DAY_04_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyTwentyOne {

	struct Day4BingoBoard {
		std::pair<int, bool> number[5][5];
	};
	
	class Day04Puzzle : public core::PuzzleBase {
	public:
		Day04Puzzle();
		~Day04Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::pair<std::vector<int>, std::vector<Day4BingoBoard>> parseInput(const std::vector<std::string>& _inputLines);

		static bool hasBoardWon(const Day4BingoBoard& _board);
		static bool applyNumber(Day4BingoBoard& _board, int _number);
		static int sumUnmarkedNumbers(const Day4BingoBoard& _board);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2021_DAY_04_PUZZLE_HPP_