#ifndef INCLUDED_ADVENT_OF_CODE_2023_DAY_13_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2023_DAY_13_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyTwentyThree {
	
	class Day13Puzzle : public core::PuzzleBase {
	public:
		Day13Puzzle();
		~Day13Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2023_DAY_13_PUZZLE_HPP_