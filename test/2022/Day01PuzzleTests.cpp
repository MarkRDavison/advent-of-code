#include <catch/catch.hpp>
#include <2022/Day01Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 1 Examples work", "[2022][Day01]") {
	    const std::vector<std::string> input = {};

	    Day01Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
