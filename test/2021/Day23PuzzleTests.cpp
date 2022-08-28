#include <catch/catch.hpp>
#include <2021/Day23Puzzle.hpp>

namespace TwentyTwentyOne {

	TEST_CASE("Day 23 Example works", "[2021][Day23]") {
		const std::vector<std::string> input = {
"#############",
"#...........#",
"###B#C#B#D###",
"  #A#D#C#A#  ",
"  #########  "
		};

		Day23Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("12521" == answers.first);
		REQUIRE("44169" == answers.second);
	}


}
