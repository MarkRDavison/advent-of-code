#include <catch/catch.hpp>
#include <2017/Day05Puzzle.hpp>

namespace TwentySeventeen {

	TEST_CASE("2017 Day 5 Examples work", "[2017][Day05]") {
	    const std::vector<std::string> input = {
"0",
"3",
"0",
"1",
"-3"
		};

	    Day05Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("5" == answers.first);
		REQUIRE("10" == answers.second);
	}

}
