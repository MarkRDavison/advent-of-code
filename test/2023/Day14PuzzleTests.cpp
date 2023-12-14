#include <catch/catch.hpp>
#include <2023/Day14Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 14 Examples work", "[2023][Day14]") {
	    const std::vector<std::string> input = {
"O....#....",
"O.OO#....#",
".....##...",
"OO.#O....O",
".O.....O#.",
"O.#..O.#.#",
"..O..#O..O",
".......O..",
"#....###..",
"#OO..#....",
		};

	    Day14Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("136" == answers.first);
		REQUIRE("64" == answers.second);
	}

}
