#include <catch/catch.hpp>
#include <2017/Day12Puzzle.hpp>

namespace TwentySeventeen {

	TEST_CASE("2017 Day 12 Examples work", "[2017][Day12]") {
	    const std::vector<std::string> input = {
"0 <-> 2",
"1 <-> 1",
"2 <-> 0, 3, 4",
"3 <-> 2, 4",
"4 <-> 2, 3, 6",
"5 <-> 6",
"6 <-> 4, 5"
		};

	    Day12Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("6" == answers.first);
		REQUIRE("2" == answers.second);
	}

}
