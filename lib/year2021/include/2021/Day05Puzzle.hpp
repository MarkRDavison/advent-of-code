#ifndef INCLUDED_ADVENT_OF_CODE_2021_DAY_05_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2021_DAY_05_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <Core/Vector2.hpp>

namespace TwentyTwentyOne {

	using VecPoints = std::vector<std::pair<Vector2i, Vector2i>>;
	
	class Day05Puzzle : public core::PuzzleBase {
	public:
		Day05Puzzle();
		~Day05Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static VecPoints parseInput(const std::vector<std::string>& _inputLines, bool _straightOnly);

		static std::string solveOverlaps(const VecPoints& _points);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2021_DAY_05_PUZZLE_HPP_