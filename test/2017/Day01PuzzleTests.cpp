#include <catch/catch.hpp>
#include <2017/Day01Puzzle.hpp>

namespace TwentySeventeen {

	TEST_CASE("2017 Day 1 Examples work", "[2017][Day01]") {
	    const std::vector<std::string> input = {
			"91213332129"
		};

	    Day01Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("15" == answers.first);
		REQUIRE("3" == answers.second);
	}

}
