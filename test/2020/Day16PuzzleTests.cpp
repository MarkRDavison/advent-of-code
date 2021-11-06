#include <catch/catch.hpp>
#include <2020/Day16Puzzle.hpp>

namespace TwentyTwenty {

	TEST_CASE("Day 16 Part 1 Example work", "[2020][Day16]") {
	    const std::vector<std::string> input = {
"departure class: 1-3 or 5-7",
"departure row: 6-11 or 33-44",
"departure seat: 13-40 or 45-50",
"",
"your ticket:",
"7,1,14",
"",
"nearby tickets:",
"7,3,47",
"40,4,50",
"55,2,20",
"38,6,12",
		};

		auto parsed = Day16Puzzle::parse(input);

		const auto part1 = Day16Puzzle::doPart1(parsed);
		const auto part2 = Day16Puzzle::doPart2(parsed);

		REQUIRE("71" == part1);
		// TODO: REQUIRE("98" == part2);
	}

}
