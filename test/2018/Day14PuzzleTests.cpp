#include <catch/catch.hpp>
#include <2018/Day14Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("2018 Day 14 Part 1 Examples work", "[2018][Day14]")
	{
		REQUIRE("5158916779" == Day14Puzzle::solvePart1(9));
		REQUIRE("0124515891" == Day14Puzzle::solvePart1(5));
		REQUIRE("9251071085" == Day14Puzzle::solvePart1(18));
		REQUIRE("5941429882" == Day14Puzzle::solvePart1(2018));
	}

	TEST_CASE("2018 Day 14 Part 2 Examples work", "[2018][Day14]")
	{
		REQUIRE("9" == Day14Puzzle::solvePart2("51589", false));
		REQUIRE("5" == Day14Puzzle::solvePart2("01245", false));
		REQUIRE("18" == Day14Puzzle::solvePart2("92510", false));
		REQUIRE("2018" == Day14Puzzle::solvePart2("59414", false));
	}

}
