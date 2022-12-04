#include <catch/catch.hpp>
#include <2022/Day04Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 4 Examples work", "[2022][Day04]") {
	    const std::vector<std::string> input = {
"2-4,6-8",
"2-3,4-5",
"5-7,7-9",
"2-8,3-7",
"6-6,4-6",
"2-6,4-8"
		};

	    Day04Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("2" == answers.first);
		REQUIRE("4" == answers.second);
	}

}
