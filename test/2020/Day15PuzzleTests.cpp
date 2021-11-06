#include <catch/catch.hpp>
#include <2020/Day15Puzzle.hpp>

namespace TwentyTwenty {

	TEST_CASE("Day 15 Examples work", "[2020][Day15]") {
	    const std::vector<std::string> input = {
			"0,3,6"
		};

		const auto& parsed = Day15Puzzle::parse(input);

		const auto part1 = Day15Puzzle::doPart(parsed, 2020);
		const auto part2 = Day15Puzzle::doPart(parsed, 30000000);

		REQUIRE("436" == part1);
		REQUIRE("175594" == part2);
	}

}
