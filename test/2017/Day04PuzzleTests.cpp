#include <catch/catch.hpp>
#include <2017/Day04Puzzle.hpp>

namespace TwentySeventeen {

	TEST_CASE("2017 Day 4 Part 1 Examples work", "[2017][Day04]") {
		const std::vector<std::string> input = {
"aa bb cc dd ee",
"aa bb cc dd aa",
"aa bb cc dd aaa"
		};

		Day04Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();
		REQUIRE("2" == answers.first);
	}

	TEST_CASE("2017 Day 4 Part 2 Examples work", "[2017][Day04]") {
		const std::vector<std::string> input = {
"abcde fghij",
"abcde xyz ecdab",
"a ab abc abd abf abj",
"iiii oiii ooii oooi oooo",
"oiii ioii iioi iiio"
		};

		Day04Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();
		REQUIRE("3" == answers.second);
	}

}
