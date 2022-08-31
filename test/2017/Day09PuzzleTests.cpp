#include <catch/catch.hpp>
#include <2017/Day09Puzzle.hpp>

namespace TwentySeventeen {

	TEST_CASE("2017 Day 9 Part 1 garbage examples work", "[2017][Day09]") {	    
		REQUIRE(0 == Day09Puzzle::removeGarbage("<>").first);
		REQUIRE(0 == Day09Puzzle::removeGarbage("<random characters>").first);
		REQUIRE(0 == Day09Puzzle::removeGarbage("<<<<>").first);
		REQUIRE(0 == Day09Puzzle::removeGarbage("<{!>}>").first);
		REQUIRE(0 == Day09Puzzle::removeGarbage("<!!>").first);
		REQUIRE(0 == Day09Puzzle::removeGarbage("<!!!>>").first);
		REQUIRE(0 == Day09Puzzle::removeGarbage("<{o\"i!a,<{i<a>").first);
	}

	TEST_CASE("2017 Day 9 Part 1 valid examples work", "[2017][Day09]") {
		REQUIRE(1 == Day09Puzzle::removeGarbage("{}").first);
		REQUIRE(6 == Day09Puzzle::removeGarbage("{{{}}}").first);
		REQUIRE(5 == Day09Puzzle::removeGarbage("{{},{}}").first);
		REQUIRE(16 == Day09Puzzle::removeGarbage("{{{},{},{{}}}}").first);
		REQUIRE(1 == Day09Puzzle::removeGarbage("{<a>,<a>,<a>,<a>}").first);
		REQUIRE(9 == Day09Puzzle::removeGarbage("{{<ab>},{<ab>},{<ab>},{<ab>}}").first);
		REQUIRE(9 == Day09Puzzle::removeGarbage("{{<!!>},{<!!>},{<!!>},{<!!>}}").first);
		REQUIRE(3 == Day09Puzzle::removeGarbage("{{<a!>},{<a!>},{<a!>},{<ab>}}").first);
	}

	TEST_CASE("2017 Day 9 Part 2 examples work", "[2017][Day09]") {
		REQUIRE(0 == Day09Puzzle::removeGarbage("<>").second);
		REQUIRE(17 == Day09Puzzle::removeGarbage("<random characters>").second);
		REQUIRE(3 == Day09Puzzle::removeGarbage("<<<<>").second);
		REQUIRE(2 == Day09Puzzle::removeGarbage("<{!>}>").second);
		REQUIRE(0 == Day09Puzzle::removeGarbage("<!!>").second);
		REQUIRE(0 == Day09Puzzle::removeGarbage("<!!!>>").second);
		REQUIRE(10 == Day09Puzzle::removeGarbage("<{o\"i!a,<{i<a>").second);
	}

}
