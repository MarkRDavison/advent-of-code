#include <catch/catch.hpp>
#include <2021/Day25Puzzle.hpp>

namespace TwentyTwentyOne {

	TEST_CASE("Day 25 Examples work", "[2021][Day25]") {
	    const std::vector<std::string> input = {
"v...>>.vv>",
".vv>>.vv..",
">>.>v>...v",
">>v>>.>.v.",
"v>v.vv.v..",
">.>>..v...",
".vv..>.>v.",
"v.v..>>v.v",
"....v..v.>"
		};

	    Day25Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
		REQUIRE("58" == answers.first);
	}

}
