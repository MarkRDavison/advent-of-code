#include <catch/catch.hpp>
#include <2017/Day19Puzzle.hpp>

namespace TwentySeventeen {

	TEST_CASE("2017 Day 19 Examples work", "[2017][Day19]") {
		const std::vector<std::string> input = {
"     |          ",
"     |  +--+    ",
"     A  |  C    ",
" F---|----E|--+ ",
"     |  |  |  D ",
"     +B-+  +--+ "
		};

	    Day19Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("ABCDEF" == answers.first);
		REQUIRE("38" == answers.second);
	}

}
