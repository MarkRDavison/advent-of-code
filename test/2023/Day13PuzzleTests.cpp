#include <catch/catch.hpp>
#include <2023/Day13Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 13 Examples work", "[2023][Day13]") {
	    const std::vector<std::string> input = {
"#.##..##.",
"..#.##.#.",
"##......#",
"##......#",
"..#.##.#.",
"..##..##.",
"#.#.##.#.",
"",
"#...##..#",
"#....#..#",
"..##..###",
"#####.##.",
"#####.##.",
"..##..###",
"#....#..#",
		};

	    Day13Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("405" == answers.first);
		REQUIRE("400" == answers.second);
	}

}
