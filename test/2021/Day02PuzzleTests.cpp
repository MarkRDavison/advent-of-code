#include <catch/catch.hpp>
#include <2021/Day02Puzzle.hpp>

namespace TwentyTwentyOne {

	TEST_CASE("Day 2 Examples work", "[2021][Day02]") {
	    const std::vector<std::string> input = {
"forward 5",
"down 5",
"forward 8",
"up 3",
"down 8",
"forward 2"
		};

	    Day02Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("150" == answers.first);
		REQUIRE("900" == answers.second);
	}

}
