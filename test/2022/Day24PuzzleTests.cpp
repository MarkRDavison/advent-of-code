#include <catch/catch.hpp>
#include <2022/Day24Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 24 Examples work", "[2022][Day24]") {
	    const std::vector<std::string> input = {
"#.######",
"#>>.<^<#",
"#.<..<<#",
"#>v.><>#",
"#<^v^^>#",
"######.#",
//"#.#####",
//"#.....#",
//"#>....#",
//"#.....#",
//"#...v.#",
//"#.....#",
//"#####.#",
		};

	    Day24Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("18" == answers.first);
		REQUIRE("54" == answers.second);
	}

}
