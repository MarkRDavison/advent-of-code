#include <catch/catch.hpp>
#include <2023/Day20Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 20 Examples work", "[2023][Day20]") {
	    const std::vector<std::string> input = {};

	    Day20Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
