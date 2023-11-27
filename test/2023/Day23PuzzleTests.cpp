#include <catch/catch.hpp>
#include <2023/Day23Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 23 Examples work", "[2023][Day23]") {
	    const std::vector<std::string> input = {};

	    Day23Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
