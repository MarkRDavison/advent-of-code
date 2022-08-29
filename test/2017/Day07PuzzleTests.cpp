#include <catch/catch.hpp>
#include <2017/Day07Puzzle.hpp>

namespace TwentySeventeen {

	TEST_CASE("2017 Day 7 Examples work", "[2017][Day07]") {
	    const std::vector<std::string> input = {
"pbga (66)",
"xhth (57)",
"ebii (61)",
"havc (66)",
"ktlj (57)",
"fwft (72) -> ktlj, cntj, xhth",
"qoyq (66)",
"padx (45) -> pbga, havc, qoyq",
"tknk (41) -> ugml, padx, fwft",
"jptl (61)",
"ugml (68) -> gyxo, ebii, jptl",
"gyxo (61)",
"cntj (57)"
		};

	    Day07Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("tknk" == answers.first);
		REQUIRE("60" == answers.second);
	}

}
