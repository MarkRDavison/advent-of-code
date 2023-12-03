#include <catch/catch.hpp>
#include <2023/Day03Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 3 Examples work", "[2023][Day03]") {
	    const std::vector<std::string> input = {
"467..114..",
"...*......",
"..35..633.",
"......#...",
"617*......",
".....+.58.",
"..592.....",
"......755.",
"...$.*....",
".664.598..",
		};

	    Day03Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("4361" == answers.first);
		REQUIRE("467835" == answers.second);
	}

}
