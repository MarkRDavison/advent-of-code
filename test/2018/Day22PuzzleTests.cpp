#include <catch/catch.hpp>
#include <2018/Day22Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("2018 Day 22 Part 1 Example work", "[2018][Day22]") {
	    const std::vector<std::string> input = {
"depth: 510",
"target: 10,10"
		};

	    Day22Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("114" == answers.first);
		REQUIRE("45" == answers.second);
	}

}
