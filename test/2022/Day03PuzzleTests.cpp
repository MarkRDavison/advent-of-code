#include <catch/catch.hpp>
#include <2022/Day03Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 3 Examples work", "[2022][Day03]") {
	    const std::vector<std::string> input = {
"vJrwpWtwJgWrhcsFMMfFFhFp",
"jqHRNqRjqzjGDLGLrsFMfFZSrLrFZsSL",
"PmmdzqPrVvPwwTWBwg",
"wMqvLMZHhHMvwLHjbvcjnnSBnvTQFn",
"ttgJtRGJQctTZtZT",
"CrZsJsPPZsGzwwsLwLmpwMDw"
		};

	    Day03Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("157" == answers.first);
		REQUIRE("70" == answers.second);
	}

}
