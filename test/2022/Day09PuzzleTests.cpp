#include <catch/catch.hpp>
#include <2022/Day09Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 9 Examples work", "[2022][Day09]") {
	    const std::vector<std::string> input = {
"R 4",
"U 4",
"L 3",
"D 1",
"R 4",
"D 1",
"L 5",
"R 2",
		};

	    Day09Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("13" == answers.first);
		REQUIRE("1" == answers.second);
	}

}
