#include <catch/catch.hpp>
#include <2023/Day16Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 16 Examples work", "[2023][Day16]") {
	    const std::vector<std::string> input = {
".|...\\....",
"|.-.\\.....",
".....|-...",
"........|.",
"..........",
".........\\",
"..../.\\\\..",
".-.-/..|..",
".|....-|.\\",
"..//.|....",
		};

	    Day16Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("46" == answers.first);
		REQUIRE("51" == answers.second);
	}

}
