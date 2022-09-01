#include <catch/catch.hpp>
#include <2017/Day15Puzzle.hpp>

namespace TwentySeventeen {

	TEST_CASE("2017 Day 15 Examples work", "[2017][Day15]") {
	    const std::vector<std::string> input = {
"Generator A starts with 65",
"Generator B starts with 8921"
		};

	    Day15Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("588" == answers.first);
		REQUIRE("309" == answers.second);
	}

}
