#ifndef INCLUDED_ADVENT_OF_CODE_2018_DAY_20_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_DAY_20_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <Core/Region.hpp>
#include <Core/Vector2.hpp>

namespace TwentyEighteen {

	struct RegularMapCell
	{
		bool doorNorthOpened{ false };
		bool doorWestOpened{ false };
		bool doorEastOpened{ false };
		bool doorSouthOpened{ false };

		bool visited() 
		{ 
			return 
				doorNorthOpened || 
				doorWestOpened  || 
				doorEastOpened  || 
				doorSouthOpened;
		}
	};

	typedef core::Region<RegularMapCell> RegularMap;
	
	class Day20Puzzle : public core::PuzzleBase {
	public:
		Day20Puzzle();
		~Day20Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2018_DAY_20_PUZZLE_HPP_