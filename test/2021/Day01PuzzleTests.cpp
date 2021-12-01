#include <catch/catch.hpp>
#include <2021/Day01Puzzle.hpp>

namespace TwentyTwentyOne {

	TEST_CASE("Day 1 Part 1 Example work", "[2021][Day01]") {
	    const std::vector<std::string> input = {
"199",
"200",
"208",
"210",
"200",
"207",
"240",
"269",
"260",
"263",
		};

	    Day01Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("7" == answers.first);
		REQUIRE("5" == answers.second);
	}

}
