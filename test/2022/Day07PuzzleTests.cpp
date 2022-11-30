#include <catch/catch.hpp>
#include <2022/Day07Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 7 Examples work", "[2022][Day07]") {
	    const std::vector<std::string> input = {};

	    Day07Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
