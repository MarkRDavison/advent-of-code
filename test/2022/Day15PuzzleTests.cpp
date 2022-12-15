#include <catch/catch.hpp>
#include <2022/Day15Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 15 Examples work", "[2022][Day15]") {
	    const std::vector<std::string> input = {
"Sensor at x=2, y=18: closest beacon is at x=-2, y=15",
"Sensor at x=9, y=16: closest beacon is at x=10, y=16",
"Sensor at x=13, y=2: closest beacon is at x=15, y=3",
"Sensor at x=12, y=14: closest beacon is at x=10, y=16",
"Sensor at x=10, y=20: closest beacon is at x=10, y=16",
"Sensor at x=14, y=17: closest beacon is at x=10, y=16",
"Sensor at x=8, y=7: closest beacon is at x=2, y=10",
"Sensor at x=2, y=0: closest beacon is at x=2, y=10",
"Sensor at x=0, y=11: closest beacon is at x=2, y=10",
"Sensor at x=20, y=14: closest beacon is at x=25, y=17",
"Sensor at x=17, y=20: closest beacon is at x=21, y=22",
"Sensor at x=16, y=7: closest beacon is at x=15, y=3",
"Sensor at x=14, y=3: closest beacon is at x=15, y=3",
"Sensor at x=20, y=1: closest beacon is at x=15, y=3",
		};

	    Day15Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve(10, 20);

		REQUIRE("26" == answers.first);
		REQUIRE("56000011" == answers.second);
	}

}
