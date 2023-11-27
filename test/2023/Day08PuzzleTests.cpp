#include <catch/catch.hpp>
#include <2023/Day08Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 8 Examples work", "[2023][Day08]") {
	    const std::vector<std::string> input = {};

	    Day08Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
