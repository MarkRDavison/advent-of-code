#ifndef INCLUDED_ADVENT_OF_CODE_2021_DAY_09_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2021_DAY_09_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <Core/Region.hpp>
#include <Core/Vector2.hpp>

namespace TwentyTwentyOne {

	using Number = int;
		
	class Day09Puzzle : public core::PuzzleBase {
	public:
		Day09Puzzle();
		~Day09Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static core::Region<Number> createHeightMap(const std::vector<std::string>& _inputLines);
		static std::vector<Vector2<Number>> findLowPoints(const core::Region<Number>& _region);
		static Number findBasinSize(const core::Region<Number>& _region, const Vector2<Number>& _lowPoint);
	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2021_DAY_09_PUZZLE_HPP_