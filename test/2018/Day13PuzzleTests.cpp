#include <catch/catch.hpp>
#include <2018/Day13Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("2018 Day 13 Examples work", "[2018][Day13]")
	{
		const std::vector<std::string> input = {
"/->-\\        ",
"|   |  /----\\",
"| /-+--+-\\  |",
"| | |  | v  |",
"\\-+-/  \\-+--/",
"  \\------/   ",
		};

		Day13Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("7,3" == answers.first);
	}

	TEST_CASE("2018 Day 13 other Examples work", "[2018][Day13]")
	{
		const std::vector<std::string> input = {
"/-\\  ",
"\\>+-\\",
"  \\</",
		};

		Day13Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("0,1" == answers.first);
	}

}
