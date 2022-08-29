#include <catch/catch.hpp>
#include <2017/Day08Puzzle.hpp>

namespace TwentySeventeen {

	TEST_CASE("2017 Day 8 Part 1 Example work", "[2017][Day08]") {
	    const std::vector<std::string> input = {
"b inc 5 if a > 1",
"a inc 1 if b < 5",
"c dec -10 if a >= 1",
"c inc -20 if c == 10"
		};

	    Day08Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("1" == answers.first);
		REQUIRE("10" == answers.second);
	}

}
