#include <catch/catch.hpp>
#include <2023/Day19Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 19 Examples work", "[2023][Day19]") {
	    const std::vector<std::string> input = {};

	    Day19Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
	}

}
