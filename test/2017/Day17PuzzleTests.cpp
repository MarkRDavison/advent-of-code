#include <catch/catch.hpp>
#include <2017/Day17Puzzle.hpp>

namespace TwentySeventeen {

	TEST_CASE("2017 Day 17 Examples work", "[2017][Day17]") {
	    const std::vector<std::string> input = { "3" };

	    Day17Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("638" == answers.first);
	}

}
