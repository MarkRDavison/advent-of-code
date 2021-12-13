#include <catch/catch.hpp>
#include <2021/Day12Puzzle.hpp>

namespace TwentyTwentyOne {

	TEST_CASE("Day 12 Examples work", "[2021][Day12]") {
		{
			const std::vector<std::string> input = {
"start-A",
"start-b",
"A-c",
"A-b",
"b-d",
"A-end",
"b-end",
			};

			Day12Puzzle puzzle{};
			puzzle.setVerbose(true);
			puzzle.setInputLines(input);

			auto answers = puzzle.fastSolve();

			REQUIRE("10" == answers.first);
			REQUIRE("36" == answers.second);
		}
		 {
			const std::vector<std::string> input = {
"dc-end",
"HN-start",
"start-kj",
"dc-start",
"dc-HN",
"LN-dc",
"HN-end",
"kj-sa",
"kj-HN",
"kj-dc",
			};

			Day12Puzzle puzzle{};
			puzzle.setVerbose(true);
			puzzle.setInputLines(input);

			auto answers = puzzle.fastSolve();

			REQUIRE("19" == answers.first);
			REQUIRE("103" == answers.second);
		}
		{
			const std::vector<std::string> input = {
"fs-end",
"he-DX",
"fs-he",
"start-DX",
"pj-DX",
"end-zg",
"zg-sl",
"zg-pj",
"pj-he",
"RW-he",
"fs-DX",
"pj-RW",
"zg-RW",
"start-pj",
"he-WI",
"zg-he",
"pj-fs",
"start-RW",
			};

			Day12Puzzle puzzle{};
			puzzle.setVerbose(true);
			puzzle.setInputLines(input);

			auto answers = puzzle.fastSolve();

			REQUIRE("226" == answers.first);
			REQUIRE("3509" == answers.second);
		}
	}

}
