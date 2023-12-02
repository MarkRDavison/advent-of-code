#ifndef INCLUDED_ADVENT_OF_CODE_2018_DAY_11_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_DAY_11_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <Core/Vector2.hpp>
#include <Core/Region.hpp>

namespace TwentyEighteen {

	typedef long ChronalChargeNumber;
	
	class Day11Puzzle : public core::PuzzleBase {
	public:
		Day11Puzzle();
		~Day11Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static core::Region<ChronalChargeNumber> CreatePowerLevels(ChronalChargeNumber serialNumber);
		static core::Region<ChronalChargeNumber> CreateSummedAreaTable(core::Region<ChronalChargeNumber> powerLevels);
		static ChronalChargeNumber GetSquareSum(core::Region<ChronalChargeNumber> powerLevels, Vector2i coords, int squareSize);
		static ChronalChargeNumber GetSquareSumUsingSAT(core::Region<ChronalChargeNumber> sat, Vector2i coords, int squareSize);
		static ChronalChargeNumber GetPowerNumber(ChronalChargeNumber serialNumber, Vector2<ChronalChargeNumber> coords);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2018_DAY_11_PUZZLE_HPP_