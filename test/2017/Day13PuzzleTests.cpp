#include <catch/catch.hpp>
#include <2017/Day13Puzzle.hpp>

namespace TwentySeventeen {

	TEST_CASE("2017 Day 13 Examples work", "[2017][Day13]") {
	    const std::vector<std::string> input = {
"0: 3",
"1: 2",
"4: 4",
"6: 4"
		};

	    Day13Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("24" == answers.first);
		REQUIRE("10" == answers.second);
	}

}
