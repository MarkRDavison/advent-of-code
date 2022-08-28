#include <catch/catch.hpp>
#include <2017/Day02Puzzle.hpp>

namespace TwentySeventeen {

	TEST_CASE("2017 Day 2 Examples work", "[2017][Day02]") {
	    const std::vector<std::string> input = {
"5 9 2 8",
"9 4 7 3",
"3 8 6 5"
		};

	    Day02Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("18" == answers.first);
		REQUIRE("9" == answers.second);
	}

}
