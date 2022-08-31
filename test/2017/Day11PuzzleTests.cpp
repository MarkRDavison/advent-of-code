#include <catch/catch.hpp>
#include <2017/Day11Puzzle.hpp>

namespace TwentySeventeen {

	TEST_CASE("2017 Day 11 Part 1 Examples work", "[2017][Day11]") {
		REQUIRE(3 == Day11Puzzle::apply("ne,ne,ne").first.length());
		REQUIRE(0 == Day11Puzzle::apply("ne,ne,sw,sw").first.length());
		REQUIRE(2 == Day11Puzzle::apply("ne,ne,s,s").first.length());
		REQUIRE(3 == Day11Puzzle::apply("se,sw,se,sw,sw").first.length());
	}

}
