#include <catch/catch.hpp>
#include <2023/Day01Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 1 Examples work", "[2023][Day01]") {
	    const std::vector<std::string> input = {};

	    Day01Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
