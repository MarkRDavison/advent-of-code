#include <catch/catch.hpp>
#include <2022/Day10Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 10 Examples work", "[2022][Day10]") {
	    const std::vector<std::string> input = {};

	    Day10Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
