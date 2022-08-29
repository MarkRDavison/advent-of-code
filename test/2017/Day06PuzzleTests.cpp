#include <catch/catch.hpp>
#include <2017/Day06Puzzle.hpp>

namespace TwentySeventeen {

	TEST_CASE("2017 Day 6 Examples work", "[2017][Day06]") {
	    const std::vector<std::string> input = {
			"0	2	7	0"
		};

	    Day06Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("5" == answers.first);
		REQUIRE("4" == answers.second);
	}

}
