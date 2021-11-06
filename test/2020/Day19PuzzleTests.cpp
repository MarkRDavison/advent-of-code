#include <catch/catch.hpp>
#include <2020/Day19Puzzle.hpp>

namespace TwentyTwenty {

	TEST_CASE("Day 19 Example 1 works", "[2020][Day19]") {
		const std::vector<std::string> input = {
"0: 1 2",
"1: \"a\"",
"2: 1 3 | 3 1",
"3: \"b\"",
"",
"aab",
"aba"
		};

		const auto& parsed = Day19Puzzle::parse(input);

		const auto part1 = Day19Puzzle::doPart1(parsed);

		REQUIRE("2" == part1);
	}

	TEST_CASE("Day 19 Examples work", "[2020][Day19]") {
		const std::vector<std::string> input = {
"0: 4 1 5",
"1: 2 3 | 3 2",
"2: 4 4 | 5 5",
"3: 4 5 | 5 4",
"4: \"a\"",
"5: \"b\"",
"",
"ababbb",
"bababa",
"abbbab",
"aaabbb",
"aaaabbb",
		};

		const auto& parsed = Day19Puzzle::parse(input);

		REQUIRE(6 == parsed.rules.size());
		REQUIRE(5 == parsed.messages.size());

		REQUIRE(1 == parsed.rules.at(0).subrules.size());
		REQUIRE(4 == parsed.rules.at(0).subrules[0].ruleIds[0]);
		REQUIRE(1 == parsed.rules.at(0).subrules[0].ruleIds[1]);
		REQUIRE(5 == parsed.rules.at(0).subrules[0].ruleIds[2]);
		REQUIRE(2 == parsed.rules.at(1).subrules.size());
		REQUIRE(2 == parsed.rules.at(1).subrules[0].ruleIds[0]);
		REQUIRE(3 == parsed.rules.at(1).subrules[0].ruleIds[1]);
		REQUIRE(3 == parsed.rules.at(1).subrules[1].ruleIds[0]);
		REQUIRE(2 == parsed.rules.at(1).subrules[1].ruleIds[1]);
		REQUIRE(2 == parsed.rules.at(2).subrules.size());
		REQUIRE(2 == parsed.rules.at(3).subrules.size());
		REQUIRE('a' == parsed.rules.at(4) .character);
		REQUIRE('b' == parsed.rules.at(5).character);

		REQUIRE("ababbb" == parsed.messages[0].message);
		REQUIRE("bababa" == parsed.messages[1].message);
		REQUIRE("abbbab" == parsed.messages[2].message);
		REQUIRE("aaabbb" == parsed.messages[3].message);
		REQUIRE("aaaabbb" == parsed.messages[4].message);

		const auto part1 = Day19Puzzle::doPart1(parsed);
		const auto part2 = Day19Puzzle::doPart2(parsed);

		REQUIRE("2" == part1);
	}

	TEST_CASE("Day 19 Example 2 works", "[2020][Day19]") {
		const std::vector<std::string> input = {
"42: 9 14 | 10 1",
"9: 14 27 | 1 26",
"10: 23 14 | 28 1",
"1: \"a\"",
"11: 42 31",
"5: 1 14 | 15 1",
"19: 14 1 | 14 14",
"12: 24 14 | 19 1",
"16: 15 1 | 14 14",
"31: 14 17 | 1 13",
"6: 14 14 | 1 14",
"2: 1 24 | 14 4",
"0: 8 11",
"13: 14 3 | 1 12",
"15: 1 | 14",
"17: 14 2 | 1 7",
"23: 25 1 | 22 14",
"28: 16 1",
"4: 1 1",
"20: 14 14 | 1 15",
"3: 5 14 | 16 1",
"27: 1 6 | 14 18",
"14: \"b\"",
"21: 14 1 | 1 14",
"25: 1 1 | 1 14",
"22: 14 14",
"8: 42",
"26: 14 22 | 1 20",
"18: 15 15",
"7: 14 5 | 1 21",
"24: 14 1",
"",
"abbbbbabbbaaaababbaabbbbabababbbabbbbbbabaaaa",
"bbabbbbaabaabba",
"babbbbaabbbbbabbbbbbaabaaabaaa",
"aaabbbbbbaaaabaababaabababbabaaabbababababaaa",
"bbbbbbbaaaabbbbaaabbabaaa",
"bbbababbbbaaaaaaaabbababaaababaabab",
"ababaaaaaabaaab",
"ababaaaaabbbaba",
"baabbaaaabbaaaababbaababb",
"abbbbabbbbaaaababbbbbbaaaababb",
"aaaaabbaabaaaaababaa",
"aaaabbaaaabbaaa",
"aaaabbaabbaaaaaaabbbabbbaaabbaabaaa",
"babaaabbbaaabaababbaabababaaab",
"aabbbbbaabbbaaaaaabbbbbababaaaaabbaaabba",
		};

		const auto& parsed1 = Day19Puzzle::parse(input);
		const auto& parsed2 = Day19Puzzle::transformPart1ToPart2(parsed1);

		REQUIRE(1 == parsed1.rules.at(8).subrules.size());
		REQUIRE(2 == parsed2.rules.at(8).subrules.size());

		REQUIRE(1 == parsed1.rules.at(11).subrules.size());
		REQUIRE(2 == parsed2.rules.at(11).subrules.size());

		REQUIRE(Day19Puzzle::matchRule(parsed2, 0, "bbabbbbaabaabba"));
		REQUIRE(Day19Puzzle::matchRule(parsed2, 0, "babbbbaabbbbbabbbbbbaabaaabaaa"));
		REQUIRE(Day19Puzzle::matchRule(parsed2, 0, "aaabbbbbbaaaabaababaabababbabaaabbababababaaa"));
		REQUIRE(Day19Puzzle::matchRule(parsed2, 0, "bbbbbbbaaaabbbbaaabbabaaa"));
		REQUIRE(Day19Puzzle::matchRule(parsed2, 0, "bbbababbbbaaaaaaaabbababaaababaabab"));
		REQUIRE(Day19Puzzle::matchRule(parsed2, 0, "ababaaaaaabaaab"));
		REQUIRE(Day19Puzzle::matchRule(parsed2, 0, "ababaaaaabbbaba"));
		REQUIRE(Day19Puzzle::matchRule(parsed2, 0, "baabbaaaabbaaaababbaababb"));
		REQUIRE(Day19Puzzle::matchRule(parsed2, 0, "abbbbabbbbaaaababbbbbbaaaababb"));
		REQUIRE(Day19Puzzle::matchRule(parsed2, 0, "aaaaabbaabaaaaababaa"));
		REQUIRE(Day19Puzzle::matchRule(parsed2, 0, "aaaabbaabbaaaaaaabbbabbbaaabbaabaaa"));
		REQUIRE(Day19Puzzle::matchRule(parsed2, 0, "aabbbbbaabbbaaaaaabbbbbababaaaaabbaaabba"));
	}

}
