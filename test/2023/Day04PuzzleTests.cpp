#include <catch/catch.hpp>
#include <2023/Day04Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 4 Examples work", "[2023][Day04]") {
	    const std::vector<std::string> input = {};

	    Day04Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
