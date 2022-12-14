#include <catch/catch.hpp>
#include <2022/Day14Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 14 Examples work", "[2022][Day14]") {
	    const std::vector<std::string> input = {
"498,4 -> 498,6 -> 496,6",
"503,4 -> 502,4 -> 502,9 -> 494,9"
		};

	    Day14Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("24" == answers.first);
		REQUIRE("93" == answers.second);
	}

}
