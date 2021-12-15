#include <catch/catch.hpp>
#include <2021/Day15Puzzle.hpp>

namespace TwentyTwentyOne {

	TEST_CASE("Day 15 Examples work", "[2021][Day15]") {
	    const std::vector<std::string> input = {
"1163751742",
"1381373672",
"2136511328",
"3694931569",
"7463417111",
"1319128137",
"1359912421",
"3125421639",
"1293138521",
"2311944581",
		};

	    Day15Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("40" == answers.first);
		REQUIRE("315" == answers.second);
	}

}
