#include <catch/catch.hpp>
#include <2018/Day09Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("2018 Day 9 Examples work", "[2018][Day09]") {
	    const std::vector<std::string> input = { 
			"9 players; last marble is worth 25 points" 
		};

	    Day09Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("32" == answers.first);
		REQUIRE("22563" == answers.second);
	}

	TEST_CASE("2018 Day 9 solve works", "[2018][Day09]")
	{
		REQUIRE(8317 == Day09Puzzle::solve(10, 1618));
		REQUIRE(146373 == Day09Puzzle::solve(13, 7999));
		REQUIRE(2764 == Day09Puzzle::solve(17, 1104));
		REQUIRE(54718 == Day09Puzzle::solve(21, 6111));
		REQUIRE(37305 == Day09Puzzle::solve(30, 5807));
	}
	
}
