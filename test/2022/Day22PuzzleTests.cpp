#include <catch/catch.hpp>
#include <2022/Day22Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 22 Examples work", "[2022][Day22]") {
	    const std::vector<std::string> input = {};

	    Day22Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
