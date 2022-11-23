#include <catch/catch.hpp>
#include <2018/Day06Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("2018 Day 6 Examples work", "[2018][Day06]") {
	    const std::vector<std::string> input = {
"1, 1",
"1, 6",
"8, 3",
"3, 4",
"5, 5",
"8, 9"
		};

	    Day06Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve(32);

		REQUIRE("17" == answers.first);
		REQUIRE("16" == answers.second);
	}

}
