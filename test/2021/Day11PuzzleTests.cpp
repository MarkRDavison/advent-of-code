#include <catch/catch.hpp>
#include <2021/Day11Puzzle.hpp>

namespace TwentyTwentyOne {

	TEST_CASE("Day 11 Examples work", "[2021][Day11]") {
		const std::vector<std::string> input = {
"5483143223",
"2745854711",
"5264556173",
"6141336146",
"6357385478",
"4167524645",
"2176841721",
"6882881134",
"4846848554",
"5283751526",
		};

		Day11Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("1656" == answers.first);
		REQUIRE("195" == answers.second);
	}

	TEST_CASE("Day 11 iterating works", "[2021][Day11]") {
		const std::vector<std::string> input = {
"5483143223",
"2745854711",
"5264556173",
"6141336146",
"6357385478",
"4167524645",
"2176841721",
"6882881134",
"4846848554",
"5283751526",
		};

		auto region = Day11Puzzle::parse(input);

		REQUIRE(Day11Puzzle::validate(region, input));
		REQUIRE(0 == Day11Puzzle::iterate(region));
		REQUIRE(Day11Puzzle::validate(region, {
"6594254334",
"3856965822",
"6375667284",
"7252447257",
"7468496589",
"5278635756",
"3287952832",
"7993992245",
"5957959665",
"6394862637",
		}));
		REQUIRE(35 == Day11Puzzle::iterate(region));
		REQUIRE(Day11Puzzle::validate(region, {
"8807476555",
"5089087054",
"8597889608",
"8485769600",
"8700908800",
"6600088989",
"6800005943",
"0000007456",
"9000000876",
"8700006848",
			}));
		REQUIRE(45 == Day11Puzzle::iterate(region));
		REQUIRE(Day11Puzzle::validate(region, {
"0050900866",
"8500800575",
"9900000039",
"9700000041",
"9935080063",
"7712300000",
"7911250009",
"2211130000",
"0421125000",
"0021119000",
			}));

		region = Day11Puzzle::parse(input);
		long part1 = 0;
		for (unsigned i = 1; i <= 100; ++i) {
			long current = Day11Puzzle::iterate(region);
			part1 += current;
			if (i == 10) {

				REQUIRE(29 == current);
				REQUIRE(Day11Puzzle::validate(region, {
"0481112976",
"0031112009",
"0041112504",
"0081111406",
"0099111306",
"0093511233",
"0442361130",
"5532252350",
"0532250600",
"0032240000",
					}));
			}
		}

		REQUIRE(1656 == part1);
	}


	TEST_CASE("Day 11 day 2 works", "[2021][Day11]") {
		const std::vector<std::string> input = {
"5483143223",
"2745854711",
"5264556173",
"6141336146",
"6357385478",
"4167524645",
"2176841721",
"6882881134",
"4846848554",
"5283751526",
		};
		
		auto region = Day11Puzzle::parse(input);

		for (long i = 1; i <= 195; ++i) {
			long current= Day11Puzzle::iterate(region);

			if (i == 193) {
				REQUIRE(0 == current);
				REQUIRE(Day11Puzzle::validate(region, {
"5877777777",
"8877777777",
"7777777777",
"7777777777",
"7777777777",
"7777777777",
"7777777777",
"7777777777",
"7777777777",
"7777777777",
					}));
			}
			if (i == 194) {
				REQUIRE(0 == current);
				REQUIRE(Day11Puzzle::validate(region, {
		"6988888888",
		"9988888888",
		"8888888888",
		"8888888888",
		"8888888888",
		"8888888888",
		"8888888888",
		"8888888888",
		"8888888888",
		"8888888888",
					}));
			}
			if (i == 195) {
				REQUIRE(100 == current);
				REQUIRE(Day11Puzzle::validate(region, {
		"0000000000",
		"0000000000",
		"0000000000",
		"0000000000",
		"0000000000",
		"0000000000",
		"0000000000",
		"0000000000",
		"0000000000",
		"0000000000",
					}));
			}
		}


	}
}
