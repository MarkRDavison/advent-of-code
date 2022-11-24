#include <catch/catch.hpp>
#include <2018/Day08Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("2018 Day 8 Examples work", "[2018][Day08]") {
	    const std::vector<std::string> input = { "2 3 0 3 10 11 12 1 1 0 1 99 2 1 1 2" };

	    Day08Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("138" == answers.first);
		REQUIRE("66" == answers.second);
	}

}
