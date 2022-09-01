#include <catch/catch.hpp>
#include <2017/Day14Puzzle.hpp>

namespace TwentySeventeen {

	TEST_CASE("2017 Day 14 Examples work", "[2017][Day14]") {
	    const std::vector<std::string> input = {
			"flqrgnkx"
		};

	    Day14Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("8108" == answers.first);
		REQUIRE("1242" == answers.second);
	}

}
