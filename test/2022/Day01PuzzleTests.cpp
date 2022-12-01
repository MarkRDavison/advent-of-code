#include <catch/catch.hpp>
#include <2022/Day01Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 1 Examples work", "[2022][Day01]") {
	    const std::vector<std::string> input = {
"1000",
"2000",
"3000",
"",
"4000",
"",
"5000",
"6000",
"",
"7000",
"8000",
"9000",
"",
"10000"
		};

	    Day01Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("24000" == answers.first);
		REQUIRE("45000" == answers.second);
	}

}
