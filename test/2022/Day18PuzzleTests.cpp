#include <catch/catch.hpp>
#include <2022/Day18Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 18 Examples work", "[2022][Day18]") {
	    const std::vector<std::string> input = {
"2,2,2",
"1,2,2",
"3,2,2",
"2,1,2",
"2,3,2",
"2,2,1",
"2,2,3",
"2,2,4",
"2,2,6",
"1,2,5",
"3,2,5",
"2,1,5",
"2,3,5",
		};

	    Day18Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("64" == answers.first);
		REQUIRE("58" == answers.second);
	}

}
