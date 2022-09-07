#include <catch/catch.hpp>
#include <2017/Day22Puzzle.hpp>

namespace TwentySeventeen {

	TEST_CASE("2017 Day 22 Examples work", "[2017][Day22]") {
	    const std::vector<std::string> input = {
"..#",
"#..",
"..."
		};

	    Day22Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve(70, 100);

		CHECK("41" == answers.first);
		REQUIRE("26" == answers.second);
	}

}
