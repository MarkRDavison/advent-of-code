#include <catch/catch.hpp>
#include <2023/Day24Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 24 Examples work", "[2023][Day24]") {
	    const std::vector<std::string> input = {};

	    Day24Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
