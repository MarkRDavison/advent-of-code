#include <catch/catch.hpp>
#include <2023/Day15Puzzle.hpp>

namespace TwentyTwentyThree {
	TEST_CASE("Day 15 hash works", "[2023][Day15]")
	{
		REQUIRE(52 == Day15Puzzle::hash("HASH"));
	}

	TEST_CASE("Day 15 Examples work", "[2023][Day15]") {
	    const std::vector<std::string> input = {
			"rn=1,cm-,qp=3,cm=2,qp-,pc=4,ot=9,ab=5,pc-,pc=6,ot=7",
			""
		};

	    Day15Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("1320" == answers.first);
		REQUIRE("145" == answers.second);
	}

}
