#include <catch/catch.hpp>
#include <2017/Day16Puzzle.hpp>

namespace TwentySeventeen {

	TEST_CASE("2017 Day 16 Examples work", "[2017][Day16]") {
	    const std::vector<std::string> input = {
			"s1,x3/4,pe/b"
		};

	    Day16Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve(5);

		REQUIRE("baedc" == answers.first);
		REQUIRE("baedc" == answers.second);
	}

}
