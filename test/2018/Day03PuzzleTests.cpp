#include <catch/catch.hpp>
#include <2018/Day03Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("2018 Day 3 Examples work", "[2018][Day03]") {
	    const std::vector<std::string> input = {
"#1 @ 1,3: 4x4",
"#2 @ 3,1: 4x4",
"#3 @ 5,5: 2x2"
		};

	    Day03Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("4" == answers.first);
		REQUIRE("3" == answers.second);
	}

}
