#include <catch/catch.hpp>
#include <2018/Day18Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("2018 Day 18 Examples work", "[2018][Day18]") {
	    const std::vector<std::string> input = {
".#.#...|#.",
".....#|##|",
".|..|...#.",
"..|#.....#",
"#.#|||#|#|",
"...#.||...",
".|....|...",
"||...#|.#|",
"|.||||..|.",
"...#.|..|.",
		};

	    Day18Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("1147" == answers.first);
	}

}
