#include <catch/catch.hpp>
#include <2022/Day25Puzzle.hpp>
#include <unordered_map>

namespace TwentyTwentyTwo {
	TEST_CASE("Day 25 SNAFU <-> DECIMAL works", "[2022][Day25]")
	{
		const std::unordered_map<long long, std::string> numberMap = {
{        1,              "1"},
{        2,              "2"},
{        3,             "1="},
{        4,             "1-"},
{        5,             "10"},
{        6,             "11"},
{        7,             "12"},
{        8,             "2="},
{        9,             "2-"},
{       10,             "20"},
{       15,            "1=0"},
{       20,            "1-0"},
{     2022,         "1=11-2"},
{    12345,        "1-0---0"},
{314159265,  "1121-1110-1=0"}
		};

		for (const auto& [decimal, snafu] : numberMap)
		{
			REQUIRE(decimal == Day25Puzzle::SnafuToDecimal(snafu));
			REQUIRE(snafu == Day25Puzzle::DecimalToSnafu(decimal));
		}
	}

	TEST_CASE("Day 25 Examples work", "[2022][Day25]") {
	    const std::vector<std::string> input = {
"1=-0-2",
"12111",
"2=0=",
"21",
"2=01",
"111",
"20012",
"112",
"1=-1=",
"1-12",
"12",
"1=",
"122",
		};

	    Day25Puzzle puzzle{};
	    puzzle.setVerbose(true);
	    puzzle.setInputLines(input);

	    auto answers = puzzle.fastSolve();
		
		REQUIRE("2=-1=0" == answers.first);
	}

}
