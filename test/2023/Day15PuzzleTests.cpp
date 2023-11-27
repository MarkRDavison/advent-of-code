#include <catch/catch.hpp>
#include <2023/Day15Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 15 Examples work", "[2023][Day15]") {
	    const std::vector<std::string> input = {};

	    Day15Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
