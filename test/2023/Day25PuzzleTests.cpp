#include <catch/catch.hpp>
#include <2023/Day25Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 25 Examples work", "[2023][Day25]") {
	    const std::vector<std::string> input = {};

	    Day25Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
