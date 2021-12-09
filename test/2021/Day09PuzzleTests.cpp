#include <catch/catch.hpp>
#include <2021/Day09Puzzle.hpp>

namespace TwentyTwentyOne {

	TEST_CASE("Day 9 Examples work", "[2021][Day09]") {
	    const std::vector<std::string> input = {
"2199943210",
"3987894921",
"9856789892",
"8767896789",
"9899965678",
		};

	    Day09Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("15" == answers.first);
		REQUIRE("1134" == answers.second);
	}

}
