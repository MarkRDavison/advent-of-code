#include <catch/catch.hpp>
#include <2023/Day13Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 13 Examples work", "[2023][Day13]") {
	    const std::vector<std::string> input = {};

	    Day13Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
