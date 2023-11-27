#include <catch/catch.hpp>
#include <2023/Day17Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 17 Examples work", "[2023][Day17]") {
	    const std::vector<std::string> input = {};

	    Day17Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
