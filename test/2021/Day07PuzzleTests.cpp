#include <catch/catch.hpp>
#include <2021/Day07Puzzle.hpp>

namespace TwentyTwentyOne {

	TEST_CASE("Day 7 Examples work", "[2021][Day07]") {
		const std::vector<std::string> input = {
			"16,1,2,0,4,2,7,1,2,14"
		};

		Day07Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("37" == answers.first);
		REQUIRE("168" == answers.second);
	}

	TEST_CASE("Day 7 Solve for position works", "[2021][Day07]") {
		std::map<long, int> crabLocations = {
			{16, 1}, {1, 2}, {2, 3}, {0, 1}, {4, 1}, {7, 1}, {14, 1}
		};

		REQUIRE(41 == Day07Puzzle::solveForPosition(crabLocations, 1, true));
		REQUIRE(37 == Day07Puzzle::solveForPosition(crabLocations, 2, true));
		REQUIRE(39 == Day07Puzzle::solveForPosition(crabLocations, 3, true));
		REQUIRE(71 == Day07Puzzle::solveForPosition(crabLocations, 10, true));

		REQUIRE(242 == Day07Puzzle::solveForPosition(crabLocations, 1, false));
		REQUIRE(206 == Day07Puzzle::solveForPosition(crabLocations, 2, false));
		REQUIRE(183 == Day07Puzzle::solveForPosition(crabLocations, 3, false));
		REQUIRE(311 == Day07Puzzle::solveForPosition(crabLocations, 10, false));
	}

}
