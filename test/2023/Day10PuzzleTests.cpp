#include <catch/catch.hpp>
#include <2023/Day10Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 10 Examples work", "[2023][Day10]") {
	    const std::vector<std::string> input = {};

	    Day10Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
