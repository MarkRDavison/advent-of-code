#include <catch/catch.hpp>
#include <2020/Day14Puzzle.hpp>

namespace TwentyTwenty {

	TEST_CASE("Day 14 Part 1 Example work", "[2020][Day14]") {
		const std::vector<std::string> input = {
"mask = XXXXXXXXXXXXXXXXXXXXXXXXXXXXX1XXXX0X",
"mem[8] = 11",
"mem[7] = 101",
"mem[8] = 0",
		};

		const auto& parsed = Day14Puzzle::parse(input);

		const auto part1 = Day14Puzzle::doPart1(parsed);

		REQUIRE("165" == part1);
	}

	TEST_CASE("Day 14 Examples work", "[2020][Day14]") {
		const std::vector<std::string> input = {
"mask = 000000000000000000000000000000X1001X",
"mem[42] = 100",
"mask = 00000000000000000000000000000000X0XX",
"mem[26] = 1",
		};

		const auto& parsed = Day14Puzzle::parse(input);

		const auto part2 = Day14Puzzle::doPart2(parsed);

		REQUIRE("208" == part2);
	}

}
