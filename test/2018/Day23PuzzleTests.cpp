#include <catch/catch.hpp>
#include <2018/Day23Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("2018 Day 23 Examples work", "[2018][Day23]") {
	    const std::vector<std::string> input = {
"pos=<10,12,12>, r=2",
"pos=<12,14,12>, r=2",
"pos=<16,12,12>, r=4",
"pos=<14,14,14>, r=6",
"pos=<50,50,50>, r=200",
"pos=<10,10,10>, r=5",
		};

	    Day23Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("6" == answers.first);
		REQUIRE("36" == answers.second);
	}

}
