#include <catch/catch.hpp>
#include <2023/Day14Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 14 Examples work", "[2023][Day14]") {
	    const std::vector<std::string> input = {};

	    Day14Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
