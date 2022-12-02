#include <catch/catch.hpp>
#include <2022/Day02Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 2 Examples work", "[2022][Day02]") {
	    const std::vector<std::string> input = {
"A Y",
"B X",
"C Z"
		};

	    Day02Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("15" == answers.first);
		REQUIRE("12" == answers.second);
	}

}
