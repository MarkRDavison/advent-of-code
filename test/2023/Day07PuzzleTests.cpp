#include <catch/catch.hpp>
#include <2023/Day07Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 7 isFiveOfAKind works", "[2023][Day07]")
	{
		REQUIRE(Day07Puzzle::isFiveOfAKind("AAAAA", false));
		REQUIRE(Day07Puzzle::isFiveOfAKind("KKKKK", false));
		REQUIRE(Day07Puzzle::isFiveOfAKind("22222", false));
		REQUIRE(Day07Puzzle::isFiveOfAKind("TTTTT", false));
		REQUIRE(Day07Puzzle::isFiveOfAKind("33333", false));
	}

	TEST_CASE("Day 7 isFourOfAKind works", "[2023][Day07]")
	{
		REQUIRE_FALSE(Day07Puzzle::isFiveOfAKind("5AAAA", false));
		REQUIRE_FALSE(Day07Puzzle::isFiveOfAKind("K5KKK", false));
		REQUIRE_FALSE(Day07Puzzle::isFiveOfAKind("22522", false));
		REQUIRE_FALSE(Day07Puzzle::isFiveOfAKind("TTT5T", false));
		REQUIRE_FALSE(Day07Puzzle::isFiveOfAKind("33335", false));

		REQUIRE(Day07Puzzle::isFourOfAKind("5AAAA", false));
		REQUIRE(Day07Puzzle::isFourOfAKind("K5KKK", false));
		REQUIRE(Day07Puzzle::isFourOfAKind("22522", false));
		REQUIRE(Day07Puzzle::isFourOfAKind("TTT5T", false));
		REQUIRE(Day07Puzzle::isFourOfAKind("33335", false));
	}

	TEST_CASE("Day 7 isThreeOfAKind works", "[2023][Day07]")
	{
		REQUIRE(Day07Puzzle::isThreeOfAKind("53AAA", false));
		REQUIRE(Day07Puzzle::isThreeOfAKind("5A3AA", false));
		REQUIRE(Day07Puzzle::isThreeOfAKind("5AA3A", false));
		REQUIRE(Day07Puzzle::isThreeOfAKind("5AAA3", false));
		REQUIRE(Day07Puzzle::isThreeOfAKind("A35AA", false));
		REQUIRE(Day07Puzzle::isThreeOfAKind("AA53A", false));
		REQUIRE(Day07Puzzle::isThreeOfAKind("AAA35", false));

		REQUIRE_FALSE(Day07Puzzle::isFullHouse("53AAA", false));
		REQUIRE_FALSE(Day07Puzzle::isFullHouse("5A3AA", false));
		REQUIRE_FALSE(Day07Puzzle::isFullHouse("5AA3A", false));
		REQUIRE_FALSE(Day07Puzzle::isFullHouse("5AAA3", false));
		REQUIRE_FALSE(Day07Puzzle::isFullHouse("A35AA", false));
		REQUIRE_FALSE(Day07Puzzle::isFullHouse("AA53A", false));
		REQUIRE_FALSE(Day07Puzzle::isFullHouse("AAA35", false));
	}

	TEST_CASE("Day 7 isFullHouse works", "[2023][Day07]")
	{
		REQUIRE(Day07Puzzle::isFullHouse("55AAA", false));
		REQUIRE(Day07Puzzle::isFullHouse("5A5AA", false));
		REQUIRE(Day07Puzzle::isFullHouse("5AA5A", false));
		REQUIRE(Day07Puzzle::isFullHouse("5AAA5", false));
		REQUIRE(Day07Puzzle::isFullHouse("A55AA", false));
		REQUIRE(Day07Puzzle::isFullHouse("AA55A", false));
		REQUIRE(Day07Puzzle::isFullHouse("AAA55", false));

		REQUIRE_FALSE(Day07Puzzle::isThreeOfAKind("55AAA", false));
		REQUIRE_FALSE(Day07Puzzle::isThreeOfAKind("5A5AA", false));
		REQUIRE_FALSE(Day07Puzzle::isThreeOfAKind("5AA5A", false));
		REQUIRE_FALSE(Day07Puzzle::isThreeOfAKind("5AAA5", false));
		REQUIRE_FALSE(Day07Puzzle::isThreeOfAKind("A55AA", false));
		REQUIRE_FALSE(Day07Puzzle::isThreeOfAKind("AA55A", false));
		REQUIRE_FALSE(Day07Puzzle::isThreeOfAKind("AAA55", false));
	}

	TEST_CASE("Day 7 isTwoPair works", "[2023][Day07]")
	{
		REQUIRE(Day07Puzzle::isTwoPair("55AA4", false));
		REQUIRE(Day07Puzzle::isTwoPair("545AA", false));
		REQUIRE(Day07Puzzle::isTwoPair("5A45A", false));
		REQUIRE(Day07Puzzle::isTwoPair("5A4A5", false));
		REQUIRE(Day07Puzzle::isTwoPair("A55A4", false));
		REQUIRE(Day07Puzzle::isTwoPair("4A55A", false));
		REQUIRE(Day07Puzzle::isTwoPair("A4A55", false));
	}

	TEST_CASE("Day 7 isOnePair works", "[2023][Day07]")
	{
		REQUIRE(Day07Puzzle::isOnePair("55JA4", false));
		REQUIRE(Day07Puzzle::isOnePair("545JA", false));
		REQUIRE(Day07Puzzle::isOnePair("5J45A", false));
		REQUIRE(Day07Puzzle::isOnePair("5J4A5", false));
		REQUIRE(Day07Puzzle::isOnePair("J55A4", false));
		REQUIRE(Day07Puzzle::isOnePair("4A55J", false));
		REQUIRE(Day07Puzzle::isOnePair("J4A55", false));
	}

	TEST_CASE("Day 7 isHighCard works", "[2023][Day07]")
	{
		REQUIRE(Day07Puzzle::isHighCard("23456", false));
		REQUIRE(Day07Puzzle::isHighCard("62345", false));
		REQUIRE(Day07Puzzle::isHighCard("56234", false));
	}

	TEST_CASE("Day 7 CompareHand misc examples works", "[2023][Day07]")
	{
		REQUIRE(-1 == Day07Puzzle::CompareHand("33332", "2AAAA", false));
		REQUIRE(+1 == Day07Puzzle::CompareHand("2AAAA", "33332", false));
	}

	TEST_CASE("Day 7 Examples work", "[2023][Day07]")
	{
		const std::vector<std::string> input = {
"32T3K 765",
"T55J5 684",
"KK677 28",
"KTJJT 220",
"QQQJA 483",
		};

		Day07Puzzle puzzle{};
		puzzle.setVerbose(true);
		puzzle.setInputLines(input);

		auto answers = puzzle.fastSolve();

		REQUIRE("6440" == answers.first);
		REQUIRE("5905" == answers.second);
	}	

}
