#include <catch/catch.hpp>
#include <2022/Day11Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 11 Examples work", "[2022][Day11]") {
	    const std::vector<std::string> input = {};

	    Day11Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
