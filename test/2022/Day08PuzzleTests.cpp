#include <catch/catch.hpp>
#include <2022/Day08Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 8 Examples work", "[2022][Day08]") {
	    const std::vector<std::string> input = {
"30373",
"25512",
"65332",
"33549",
"35390",
		};

	    Day08Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("21" == answers.first);
		REQUIRE("8" == answers.second);
	}

}
