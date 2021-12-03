#include <catch/catch.hpp>
#include <2021/Day03Puzzle.hpp>

namespace TwentyTwentyOne {

	TEST_CASE("Day 3 Examples work", "[2021][Day03]") {
	    const std::vector<std::string> input = {
"00100",
"11110",
"10110",
"10111",
"10101",
"01111",
"00111",
"11100",
"10000",
"11001",
"00010",
"01010",
		};

	    Day03Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("198" == answers.first);
		REQUIRE("230" == answers.second);
	}

}
