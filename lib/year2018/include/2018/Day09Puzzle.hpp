#ifndef INCLUDED_ADVENT_OF_CODE_2018_DAY_09_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_DAY_09_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyEighteen {
	
	class Day09Puzzle : public core::PuzzleBase {
	public:
		Day09Puzzle();
		~Day09Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static long long solve(long long _players, long long _marbles);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2018_DAY_09_PUZZLE_HPP_