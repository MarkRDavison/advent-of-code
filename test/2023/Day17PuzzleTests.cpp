#include <catch/catch.hpp>
#include <2023/Day17Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 17 Example # 1 work", "[2023][Day17]")
	{
		const std::vector<std::string> input = {
"2413432311323",
"3215453535623",
"3255245654254",
"3446585845452",
"4546657867536",
"1438598798454",
"4457876987766",
"3637877979653",
"4654967986887",
"4564679986453",
"1224686865563",
"2546548887735",
"4322674655533",
		};

		Day17Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("102" == answers.first);
		REQUIRE("94" == answers.second);
	}
	TEST_CASE("Day 17 Example # 2 work", "[2023][Day17]")
	{
		const std::vector<std::string> input = {
"111111111111",
"999999999991",
"999999999991",
"999999999991",
"999999999991",
		};

		Day17Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("71" == answers.second);
	}

}
