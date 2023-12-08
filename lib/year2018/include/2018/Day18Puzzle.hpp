#ifndef INCLUDED_ADVENT_OF_CODE_2018_DAY_18_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_DAY_18_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <Core/Region.hpp>

namespace TwentyEighteen {

	typedef core::Region<char> LumberMap;
	
	class Day18Puzzle : public core::PuzzleBase {
	public:
		Day18Puzzle();
		~Day18Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static void iterate(const LumberMap& current, LumberMap& next);
		static void draw(const LumberMap& map, int iteration);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2018_DAY_18_PUZZLE_HPP_