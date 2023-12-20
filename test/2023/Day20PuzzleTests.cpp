#include <catch/catch.hpp>
#include <2023/Day20Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 20 Example #1 works", "[2023][Day20]")
	{
		const std::vector<std::string> input = {
"broadcaster -> a, b, c",
"%a -> b",
"%b -> c",
"%c -> inv",
"&inv -> a",
		};

		Day20Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("32000000" == answers.first);
	}

	TEST_CASE("Day 20 Example #2 works", "[2023][Day20]")
	{
		const std::vector<std::string> input = {
"broadcaster -> a",
"%a -> inv, con",
"&inv -> b",
"%b -> con",
"&con -> output",
		};

		Day20Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("11687500" == answers.first);
	}

}
