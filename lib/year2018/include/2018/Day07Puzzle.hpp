#ifndef INCLUDED_ADVENT_OF_CODE_2018_DAY_07_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_DAY_07_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyEighteen {
	
	class Day07Puzzle : public core::PuzzleBase {
	public:
		Day07Puzzle();
		~Day07Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;
		std::pair<std::string, std::string> fastSolve(int _extraTime, int _numWorkers);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2018_DAY_07_PUZZLE_HPP_