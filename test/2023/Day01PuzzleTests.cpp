#include <catch/catch.hpp>
#include <2023/Day01Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 1 Example part specific repeating works", "[2023][Day01]")
	{
		const std::vector<std::string> input = {
		"one6gmpjfouronettbbjdqsxn"
		};

		Day01Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

 		REQUIRE("66" == answers.first);
		REQUIRE("11" == answers.second);
	}

	TEST_CASE("Day 1 Example part1 work", "[2023][Day01]")
	{
		const std::vector<std::string> input = {
"1abc2",
"pqr3stu8vwx",
"a1b2c3d4e5f",
"treb7uchet",
		};

		Day01Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("142" == answers.first);
	}

	TEST_CASE("Day 1 Example part2 work", "[2023][Day01]")
	{
		const std::vector<std::string> input = {
"two1nine",
"eightwothree",
"abcone2threexyz",
"xtwone3four",
"4nineeightseven2",
"zoneight234",
"7pqrstsixteen",
		};

		Day01Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("281" == answers.second);
	}

}
