#include <catch/catch.hpp>
#include <2022/Day13Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 13 Examples work", "[2022][Day13]") {
	    const std::vector<std::string> input = {
"[1,1,3,1,1]",
"[1,1,5,1,1]",
"",
"[[1],[2,3,4]]",
"[[1],4]",
"",
"[9]",
"[[8,7,6]]",
"",
"[[4,4],4,4]",
"[[4,4],4,4,4]",
"",
"[7,7,7,7]",
"[7,7,7]",
"",
"[]",
"[3]",
"",
"[[[]]]",
"[[]]",
"",
"[1,[2,[3,[4,[5,6,7]]]],8,9]",
"[1,[2,[3,[4,[5,6,0]]]],8,9]",
		};

	    Day13Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("13" == answers.first);
		REQUIRE("140" == answers.second);
	}

}
