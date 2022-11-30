#include <catch/catch.hpp>
#include <2022/Day18Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 18 Examples work", "[2022][Day18]") {
	    const std::vector<std::string> input = {};

	    Day18Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
