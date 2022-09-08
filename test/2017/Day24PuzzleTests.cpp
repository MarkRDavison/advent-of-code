#include <catch/catch.hpp>
#include <2017/Day24Puzzle.hpp>

namespace TwentySeventeen {

	TEST_CASE("2017 Day 24 Examples work", "[2017][Day24]") {
	    const std::vector<std::string> input = {
"0/2",
"2/2",
"2/3",
"3/4",
"3/5",
"0/1",
"10/1",
"9/10"
		};

	    Day24Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("31" == answers.first);
		REQUIRE("19" == answers.second);
	}

}
