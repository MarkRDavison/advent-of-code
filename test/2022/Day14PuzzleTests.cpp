#include <catch/catch.hpp>
#include <2022/Day14Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 14 Examples work", "[2022][Day14]") {
	    const std::vector<std::string> input = {};

	    Day14Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
