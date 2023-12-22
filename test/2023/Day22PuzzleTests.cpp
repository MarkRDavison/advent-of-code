#include <catch/catch.hpp>
#include <2023/Day22Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 22 Examples work", "[2023][Day22]") {
	    const std::vector<std::string> input = {
"1,0,1~1,2,1",
"0,0,2~2,0,2",
"0,2,3~2,2,3",
"0,0,4~0,2,4",
"2,0,5~2,2,5",
"0,1,6~2,1,6",
"1,1,8~1,1,9",
		};

	    Day22Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("5" == answers.first);
		REQUIRE("7" == answers.second);
	}

}
