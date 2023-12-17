#include <catch/catch.hpp>
#include <2019/Day01Puzzle.hpp>

namespace TwentyNineteen {

	TEST_CASE("2019 Day 1 getFuelRequirement works", "[2019][Day01]")
	{
		REQUIRE(2 == Day01Puzzle::getFuelRequirement(12, false));
		REQUIRE(2 == Day01Puzzle::getFuelRequirement(14, false));
		REQUIRE(654 == Day01Puzzle::getFuelRequirement(1969, false));
		REQUIRE(33583 == Day01Puzzle::getFuelRequirement(100756, false));

		REQUIRE(2 == Day01Puzzle::getFuelRequirement(12, true));
		REQUIRE(2 == Day01Puzzle::getFuelRequirement(14, true));
		REQUIRE(966 == Day01Puzzle::getFuelRequirement(1969, true));
		REQUIRE(50346 == Day01Puzzle::getFuelRequirement(100756, true));
	}

	TEST_CASE("2019 Day 1 Examples work", "[2019][Day01]") {
	    const std::vector<std::string> input = {
			"12",
			"14",
			"1969",
			"100756"
		};

		Day01Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("34241" == answers.first);
		REQUIRE("51316" == answers.second);
	}

}
