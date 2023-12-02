#include <catch/catch.hpp>
#include <2018/Day11Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("2018 Day 11 GetPowerNumber works", "[2018][Day11]")
	{
		REQUIRE(4 == Day11Puzzle::GetPowerNumber(8, { 3,5 }));
		REQUIRE(-5 == Day11Puzzle::GetPowerNumber(57, { 122,79 }));
		REQUIRE(0 == Day11Puzzle::GetPowerNumber(39, { 217,196 }));
		REQUIRE(4 == Day11Puzzle::GetPowerNumber(71, { 101,153 }));
	}

	TEST_CASE("2018 Day 11 CreatePowerLevels, GetSquareSumUsingSAT and GetSquareSum works", "[2018][Day11]") {
		auto powerLevels = Day11Puzzle::CreatePowerLevels(18);
		auto sat = Day11Puzzle::CreateSummedAreaTable(powerLevels);

		auto squareSum1 = Day11Puzzle::GetSquareSum(powerLevels, { 33,45 }, 3);
		auto satSquareSum1 = Day11Puzzle::GetSquareSumUsingSAT(sat, { 33,45 }, 3);

		REQUIRE(29 == squareSum1);
		REQUIRE(29 == satSquareSum1);

		auto squareSum2 = Day11Puzzle::GetSquareSum(powerLevels, { 90,269 }, 16);
		auto satSquareSum2 = Day11Puzzle::GetSquareSumUsingSAT(sat, { 90,269 }, 16);

		REQUIRE(113 == squareSum2);
		REQUIRE(113 == satSquareSum2);
	}

	TEST_CASE("2018 Day 11 CreateSummedAreaTable works", "[2018][Day11]")
	{
		core::Region<ChronalChargeNumber> powerLevels;
		std::vector<std::vector<ChronalChargeNumber>> examplePowerLevels = {
			{ 31, 2, 4, 33, 5, 36 },
			{12, 26, 9, 10, 29, 25},
			{13, 17, 21, 22, 20,18},
			{24,23,15,16,14,19},
			{30,8,28,27,11,7},
			{1,35,34,3,32,6}
		};
		std::vector<std::vector<ChronalChargeNumber>> expectedSummedAreaTable = {
			{31,33,37,70,75,111},
			{43,71,84,127,161,222},
			{56,101,135,200,254,333},
			{80,148,197,278,346,444},
			{110,186,263,371,450,555},
			{111,222,333,444,555,666}
		};

		for (int y = 0; y < 6; ++y)
		{
			for (int x = 0; x < 6; ++x)
			{
				powerLevels.getCell(x, y) = examplePowerLevels[y][x];
			}
		}

		auto sat = Day11Puzzle::CreateSummedAreaTable(powerLevels);

		for (int y = 0; y < 6; ++y)
		{
			for (int x = 0; x < 6; ++x)
			{
				const auto expected = expectedSummedAreaTable[y][x];
				const auto actual = sat.getCell(x, y);
				REQUIRE(expected == actual);
			}
		}

		REQUIRE(666 == Day11Puzzle::GetSquareSumUsingSAT(sat, { 0,0 }, 6));
		REQUIRE(450 == Day11Puzzle::GetSquareSumUsingSAT(sat, { 0,0 }, 5));
		REQUIRE(445 == Day11Puzzle::GetSquareSumUsingSAT(sat, { 1,0 }, 5));
	}

}
