#include <catch/catch.hpp>
#include <2023/Day02Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 2 Examples work", "[2023][Day02]") {
	    const std::vector<std::string> input = {};

	    Day02Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
