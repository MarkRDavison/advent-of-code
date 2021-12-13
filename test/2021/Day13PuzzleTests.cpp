#include <catch/catch.hpp>
#include <2021/Day13Puzzle.hpp>

namespace TwentyTwentyOne {

	TEST_CASE("Day 13 Examples work", "[2021][Day13]") {
	    const std::vector<std::string> input = {
"6,10",
"0,14",
"9,10",
"0,3",
"10,4",
"4,11",
"6,0",
"6,12",
"4,1",
"0,13",
"10,12",
"3,4",
"3,0",
"8,4",
"1,10",
"2,14",
"8,10",
"9,0",
"",
"fold along y=7",
"fold along x=5",
		};

	    Day13Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("17" == answers.first);
	}

}
