#include <catch/catch.hpp>
#include <2022/Day09Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 9 Examples work", "[2022][Day09]") {
	    const std::vector<std::string> input = {};

	    Day09Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
