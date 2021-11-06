#include <catch/catch.hpp>
#include <2020/Day23Puzzle.hpp>

namespace TwentyTwenty {

	TEST_CASE("Day 23 Examples work", "[2020][Day23][slow]") {
	    const std::vector<std::string> input = {
			"389125467"
		};

		const auto& parsed = Day23Puzzle::parse(input);

		const auto part1_10 = Day23Puzzle::doPart1(parsed, 10);
		const auto part1_100 = Day23Puzzle::doPart1(parsed, 100);
		const auto part2 = Day23Puzzle::doPart2(parsed);

		REQUIRE("92658374" == part1_10);
		REQUIRE("67384529" == part1_100);
		REQUIRE("149245887792" == part2);
	}

}
