#include <catch/catch.hpp>
#include <2018/Day19Puzzle.hpp>

namespace TwentyEighteen {

	TEST_CASE("2018 Day 19 Examples work", "[2018][Day19]") {
	    const std::vector<std::string> input = {
"#ip 0",
"seti 5 0 1",
"seti 6 0 2",
"addi 0 1 0",
"addr 1 2 3",
"setr 1 0 0",
"seti 8 0 4",
"seti 9 0 5",
		};

	    Day19Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("7" == answers.first);
		REQUIRE("12" == answers.second);
	}

}
