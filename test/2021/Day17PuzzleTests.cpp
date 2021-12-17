#include <catch/catch.hpp>
#include <2021/Day17Puzzle.hpp>

namespace TwentyTwentyOne {

	TEST_CASE("Day 17 Examples work", "[2021][Day17]") {
	    const std::vector<std::string> input = {
			"target area: x=20..30, y=-10..-5"
		};

	    Day17Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("45" == answers.first);
		REQUIRE("112" == answers.second);
	}

}
