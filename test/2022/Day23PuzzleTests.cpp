#include <catch/catch.hpp>
#include <2022/Day23Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 23 Example 1 workS", "[2022][Day23]")
	{
		const std::vector<std::string> input = {
".....",
"..##.",
"..#..",
".....",
"..##.",
".....",
		};

		Day23Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("25" == answers.first);
		REQUIRE("4" == answers.second);
	}

	TEST_CASE("Day 23 Example 2 workS", "[2022][Day23]")
	{
		const std::vector<std::string> input = {
"..............",
"..............",
".......#......",
".....###.#....",
"...#...#.#....",
"....#...##....",
"...#.###......",
"...##.#.##....",
"....#..#......",
"..............",
"..............",
"..............",
		};

		Day23Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("110" == answers.first);
		REQUIRE("20" == answers.second);
	}

}
