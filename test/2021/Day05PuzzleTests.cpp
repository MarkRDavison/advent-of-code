#include <catch/catch.hpp>
#include <2021/Day05Puzzle.hpp>

namespace TwentyTwentyOne {

	TEST_CASE("Day 5 Examples work", "[2021][Day05]") {
	    const std::vector<std::string> input = {
"0,9 -> 5,9",
"8,0 -> 0,8",
"9,4 -> 3,4",
"2,2 -> 2,1",
"7,0 -> 7,4",
"6,4 -> 2,0",
"0,9 -> 2,9",
"3,4 -> 1,4",
"0,0 -> 8,8",
"5,5 -> 8,2",
		};

	    Day05Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("5" == answers.first);
		REQUIRE("12" == answers.second);
	}

}
