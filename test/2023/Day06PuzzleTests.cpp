#include <catch/catch.hpp>
#include <2023/Day06Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 6 Examples work", "[2023][Day06]") {
	    const std::vector<std::string> input = {
"Time:      7  15   30",
"Distance:  9  40  200"
		};

	    Day06Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("288" == answers.first);
		REQUIRE("71503" == answers.second);
	}

}
