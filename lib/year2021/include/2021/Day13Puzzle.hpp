#ifndef INCLUDED_ADVENT_OF_CODE_2021_DAY_13_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2021_DAY_13_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <Core/Region.hpp>

namespace TwentyTwentyOne {

	struct Fold {
		bool horizontal;
		int index;
	};
	
	class Day13Puzzle : public core::PuzzleBase {
	public:
		Day13Puzzle();
		~Day13Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::pair<core::Region<bool>, std::vector<Fold>> parse(const std::vector<std::string>& _inputLines);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2021_DAY_13_PUZZLE_HPP_