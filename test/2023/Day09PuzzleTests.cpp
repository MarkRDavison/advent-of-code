#include <catch/catch.hpp>
#include <2023/Day09Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 9 Examples work", "[2023][Day09]") {
	    const std::vector<std::string> input = {
"0 3 6 9 12 15",
"1 3 6 10 15 21",
"10 13 16 21 30 45",
		};

	    Day09Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("114" == answers.first);
		REQUIRE("2" == answers.second);
	}

}
