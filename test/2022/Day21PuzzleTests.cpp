#include <catch/catch.hpp>
#include <2022/Day21Puzzle.hpp>

namespace TwentyTwentyTwo {

	TEST_CASE("Day 21 Examples work", "[2022][Day21]") {
	    const std::vector<std::string> input = {
"root: pppw + sjmn",
"dbpl: 5",
"cczh: sllz + lgvd",
"zczc: 2",
"ptdq: humn - dvpt",
"dvpt: 3",
"lfqf: 4",
"humn: 5",
"ljgn: 2",
"sjmn: drzm * dbpl",
"sllz: 4",
"pppw: cczh / lfqf",
"lgvd: ljgn * ptdq",
"drzm: hmdt - zczc",
"hmdt: 32",
		};

	    Day21Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();

		REQUIRE("152" == answers.first);
		REQUIRE("301" == answers.second);
	}

}
