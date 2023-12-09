#ifndef INCLUDED_ADVENT_OF_CODE_2023_DAY_09_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2023_DAY_09_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyTwentyThree {

	typedef long long MirageNumber;

	typedef std::vector<MirageNumber> MirageVector;

	struct MirageHistory
	{
		std::vector<std::vector<MirageNumber>> data;
	};

	class Day09Puzzle : public core::PuzzleBase {
	public:
		Day09Puzzle();
		~Day09Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2023_DAY_09_PUZZLE_HPP_