#include <catch/catch.hpp>
#include <2022/Day16Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 16 Examples work", "[2022][Day16]") {
	    const std::vector<std::string> input = {};

	    Day16Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
