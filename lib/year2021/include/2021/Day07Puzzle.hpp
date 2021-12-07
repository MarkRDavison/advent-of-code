#ifndef INCLUDED_ADVENT_OF_CODE_2021_DAY_07_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2021_DAY_07_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <map>

namespace TwentyTwentyOne {
	
	class Day07Puzzle : public core::PuzzleBase {
	public:
		Day07Puzzle();
		~Day07Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;
		static long solveForPosition(const std::map<long, int>& _crabLocations, long _position, bool _part1);
	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2021_DAY_07_PUZZLE_HPP_