#include <catch/catch.hpp>
#include <2022/Day09Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 9 Example 1 works", "[2022][Day09]") {
		const std::vector<std::string> input = {
"R 4",
"U 4",
"L 3",
"D 1",
"R 4",
"D 1",
"L 5",
"R 2",
		};

		Day09Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("13" == answers.first);
		REQUIRE("1" == answers.second);
	}

	TEST_CASE("Day 9 Example 2 works", "[2022][Day09]") {
		const std::vector<std::string> input = {
"R 5",
"U 8",
"L 8",
"D 3",
"R 17",
"D 10",
"L 25",
"U 20",
		};

		Day09Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("36" == answers.second);
	}

}
