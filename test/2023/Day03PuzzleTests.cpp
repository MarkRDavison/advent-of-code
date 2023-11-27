#include <catch/catch.hpp>
#include <2023/Day03Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 3 Examples work", "[2023][Day03]") {
	    const std::vector<std::string> input = {};

	    Day03Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
