#include <catch/catch.hpp>
#include <2023/Day21Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 21 Examples work", "[2023][Day21]") {
	    const std::vector<std::string> input = {};

	    Day21Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
