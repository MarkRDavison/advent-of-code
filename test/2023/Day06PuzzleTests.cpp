#include <catch/catch.hpp>
#include <2023/Day06Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 6 Examples work", "[2023][Day06]") {
	    const std::vector<std::string> input = {};

	    Day06Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
