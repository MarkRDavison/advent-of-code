#include <catch/catch.hpp>
#include <2019/Day03Puzzle.hpp>

namespace TwentyNineteen {

	TEST_CASE("2019 Day 3 Examples work", "[2019][Day03]") {
	    const std::vector<std::string> input = {
"R8,U5,L5,D3",
"U7,R6,D4,L4"
		};

	    Day03Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("6" == answers.first);
		REQUIRE("30" == answers.second);
	}

}
