#include <catch/catch.hpp>
#include <2017/Day20Puzzle.hpp>

namespace TwentySeventeen {

	TEST_CASE("2017 Day 20 Examples work", "[2017][Day20]") {
	    const std::vector<std::string> input = {
"p=<-6,0,0>, v=< 3,0,0>, a=< 0,0,0>",
"p=<-4,0,0>, v=< 2,0,0>, a=< 0,0,0>",
"p=<-2,0,0>, v=< 1,0,0>, a=< 0,0,0>",
"p=< 3,0,0>, v=<-1,0,0>, a=< 0,0,0>"
		};

	    Day20Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("0" == answers.first);
		REQUIRE("1" == answers.second);
	}

}
