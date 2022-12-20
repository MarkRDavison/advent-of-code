#include <catch/catch.hpp>
#include <2022/Day19Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 19 Examples work", "[2022][Day19][Slow]") {
	    const std::vector<std::string> input = {
"Blueprint 1: Each ore robot costs 4 ore. Each clay robot costs 2 ore. Each obsidian robot costs 3 ore and 14 clay. Each geode robot costs 2 ore and 7 obsidian.",
"Blueprint 2: Each ore robot costs 2 ore. Each clay robot costs 3 ore. Each obsidian robot costs 3 ore and 8 clay. Each geode robot costs 3 ore and 12 obsidian."
		};

	    Day19Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("33" == answers.first);
		REQUIRE("62" == answers.second);
	}

}
