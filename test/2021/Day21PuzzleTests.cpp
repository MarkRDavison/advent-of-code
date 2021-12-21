#include <catch/catch.hpp>
#include <2021/Day21Puzzle.hpp>

namespace TwentyTwentyOne {

	TEST_CASE("Day 21 Examples work", "[2021][Day21]") {
	    const std::vector<std::string> input = {
"Player 1 starting position : 4",
"Player 2 starting position : 8",
		};

	    Day21Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("739785" == answers.first);
		REQUIRE("444356092776315" == answers.second);
	}

}
