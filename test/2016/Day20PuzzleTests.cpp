#include <catch/catch.hpp>
#include <2016/Day20Puzzle.hpp>

namespace TwentySixteen {

	TEST_CASE("2016 Day 20 Examples work", "[2016][Day20]") {
	    const std::vector<std::string> input = {
"5-8",
"0-2",
"4-7"
		};

	    Day20Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve(9);

		REQUIRE("3" == answers.first);
		REQUIRE("1" == answers.second);
	}

}
