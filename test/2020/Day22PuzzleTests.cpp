#include <catch/catch.hpp>
#include <2020/Day22Puzzle.hpp>

namespace TwentyTwenty {

	TEST_CASE("Day 22 Examples work", "[2020][Day22]") {
	    const std::vector<std::string> input = {
"Player 1:",
"9",
"2",
"6",
"3",
"1",
"",
"Player 2:",
"5",
"8",
"4",
"7",
"10",
		};

		const auto& parsed = Day22Puzzle::parse(input);

		const auto part1 = Day22Puzzle::doPart1(parsed);
		const auto part2 = Day22Puzzle::doPart2(parsed);

		REQUIRE("306" == part1);
		REQUIRE("" == part2);
	}

}
