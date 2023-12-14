#include <catch/catch.hpp>
#include <2018/Day25Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("2018 Day 25 Example 1 works", "[2018][Day25]")
	{
		const std::vector<std::string> input = {
"0,0,0,0",
"3,0,0,0",
"0,3,0,0",
"0,0,3,0",
"0,0,0,3",
"0,0,0,6",
"9,0,0,0",
"12,0,0,0",
		};

		Day25Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();
		
		REQUIRE("2" == answers.first);
	}

	TEST_CASE("2018 Day 25 Example 2 works", "[2018][Day25]")
	{
		const std::vector<std::string> input = {
"-1,2,2,0",
"0,0,2,-2",
"0,0,0,-2",
"-1,2,0,0",
"-2,-2,-2,2",
"3,0,2,-1",
"-1,3,2,2",
"-1,0,-1,0",
"0,2,1,-2",
"3,0,0,0",
		};

		Day25Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();
		
		REQUIRE("4" == answers.first);
	}

}
