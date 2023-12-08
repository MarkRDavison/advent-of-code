#include <catch/catch.hpp>
#include <2023/Day08Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 8 part 1 Examples work", "[2023][Day08]") {

		REQUIRE("2" == Day08Puzzle::solvePart1({
"RL",
"",
"AAA = (BBB, CCC)",
"BBB = (DDD, EEE)",
"CCC = (ZZZ, GGG)",
"DDD = (DDD, DDD)",
"EEE = (EEE, EEE)",
"GGG = (GGG, GGG)",
"ZZZ = (ZZZ, ZZZ)",
			}));

		REQUIRE("6" == Day08Puzzle::solvePart1({
"LLR",
"",
"AAA = (BBB, BBB)",
"BBB = (AAA, ZZZ)",
"ZZZ = (ZZZ, ZZZ)",
			}));
	}

	TEST_CASE("Day 8 part 2 Examples work", "[2023][Day08]")
	{
		REQUIRE("6" == Day08Puzzle::solvePart2({
"LR",
"",
"11A = (11B, XXX)",
"11B = (XXX, 11Z)",
"11Z = (11B, XXX)",
"22A = (22B, XXX)",
"22B = (22C, 22C)",
"22C = (22Z, 22Z)",
"22Z = (22B, 22B)",
"XXX = (XXX, XXX)",
			}));
	}

}
