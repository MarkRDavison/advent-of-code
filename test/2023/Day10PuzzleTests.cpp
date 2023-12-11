#include <catch/catch.hpp>
#include <2023/Day10Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 10 Examples work", "[2023][Day10]")
	{
		const std::vector<std::string> input = {
"7-F7-",
".FJ|7",
"SJLL7",
"|F--J",
"LJ.LJ",
		};

		Day10Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("8" == answers.first);
		REQUIRE("1" == answers.second);
	}

	TEST_CASE("Day 10 Example #2 works", "[2023][Day10]")
	{
		const std::vector<std::string> input = {
"..........",
".S------7.",
".|F----7|.",
".||....||.",
".||....||.",
".|L-7F-J|.",
".|..||..|.",
".L--JL--J.",
"..........",
		};

		Day10Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("22" == answers.first);
		REQUIRE("4" == answers.second);
	}

	TEST_CASE("Day 10 Example #3 works", "[2023][Day10]")
	{
		const std::vector<std::string> input = {
".F----7F7F7F7F-7....",
".|F--7||||||||FJ....",
".||.FJ||||||||L7....",
"FJL7L7LJLJ||LJ.L-7..",
"L--J.L7...LJS7F-7L7.",
"....F-J..F7FJ|L7L7L7",
"....L7.F7||L7|.L7L7|",
".....|FJLJ|FJ|F7|.LJ",
"....FJL-7.||.||||...",
"....L---J.LJ.LJLJ...",
		};

		Day10Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("8" == answers.second);
	}

}
