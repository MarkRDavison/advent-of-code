#ifndef INCLUDED_ADVENT_OF_CODE_2019_DAY_17_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2019_DAY_17_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyNineteen {
	
	class Day17Puzzle : public core::PuzzleBase {
	public:
		Day17Puzzle();
		~Day17Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2019_DAY_17_PUZZLE_HPP_