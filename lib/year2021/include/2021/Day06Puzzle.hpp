#ifndef INCLUDED_ADVENT_OF_CODE_2021_DAY_06_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2021_DAY_06_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <unordered_map>

namespace TwentyTwentyOne {

	using LanternFishNumber = long long;
	
	class Day06Puzzle : public core::PuzzleBase {
	public:
		Day06Puzzle();
		~Day06Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::unordered_map<LanternFishNumber, LanternFishNumber> iterateLanternFish(const std::unordered_map<LanternFishNumber, LanternFishNumber>& _lanternFish);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2021_DAY_06_PUZZLE_HPP_