#include <catch/catch.hpp>
#include <2017/Day18Puzzle.hpp>

namespace TwentySeventeen {

	TEST_CASE("2017 Day 18 Example 1 works", "[2017][Day18]") {
		const std::vector<std::string> input = {
"snd 1",
"snd 2",
"snd p",
"rcv a",
"rcv b",
"rcv c",
"rcv d"
		};

		Day18Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("3" == answers.second);
	}

	TEST_CASE("2017 Day 18 Examples work", "[2017][Day18]") {
		const std::vector<std::string> input = {
"set a 1",
"add a 2",
"mul a a",
"mod a 5",
"snd a",
"set a 0",
"rcv a",
"jgz a -1",
"set a 1",
"jgz a -2"
		};

		Day18Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("4" == answers.first);
	}

}
