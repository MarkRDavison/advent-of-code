#include <catch/catch.hpp>
#include <2021/Day14Puzzle.hpp>

namespace TwentyTwentyOne {

	TEST_CASE("Day 14 Examples work", "[2021][Day14]") {
	    const std::vector<std::string> input = {
"NNCB",
"",
"CH->B",
"HH->N",
"CB->H",
"NH->C",
"HB->C",
"HC->B",
"HN->C",
"NN->C",
"BH->H",
"NC->B",
"NB->B",
"BN->B",
"BB->N",
"BC->B",
"CC->N",
"CN->C",
		};

		Day14Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("1588" == answers.first);
		REQUIRE("2188189693529" == answers.second);
	}

}
