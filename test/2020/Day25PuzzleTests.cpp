#include <catch/catch.hpp>
#include <2020/Day25Puzzle.hpp>

namespace TwentyTwenty {

	TEST_CASE("Day 25 Part 1 Example work", "[2020][Day25]") {
	    const std::vector<std::string> input = {
			"5764801", "17807724"
		};

	    Day25Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
		REQUIRE("14897079" == answers.first);
	}

}
