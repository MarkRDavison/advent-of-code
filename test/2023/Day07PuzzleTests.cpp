#include <catch/catch.hpp>
#include <2023/Day07Puzzle.hpp>

namespace TwentyTwentyThree {

	TEST_CASE("Day 7 parse works", "[2023][Day07]")
	{
		const auto hand = Day07Puzzle::parse("32TAJ");

		REQUIRE(CamelCard::_3 == hand[0]);
		REQUIRE(CamelCard::_2 == hand[1]);
		REQUIRE(CamelCard::_T == hand[2]);
		REQUIRE(CamelCard::_A == hand[3]);
		REQUIRE(CamelCard::_J == hand[4]);
	}

	TEST_CASE("Day 7 isFiveOfAKind works", "[2023][Day07]")
	{
		REQUIRE(Day07Puzzle::isFiveOfAKind(Day07Puzzle::parse("AAAAA")));
		REQUIRE(Day07Puzzle::isFiveOfAKind(Day07Puzzle::parse("KKKKK")));
		REQUIRE(Day07Puzzle::isFiveOfAKind(Day07Puzzle::parse("22222")));
		REQUIRE(Day07Puzzle::isFiveOfAKind(Day07Puzzle::parse("TTTTT")));
		REQUIRE(Day07Puzzle::isFiveOfAKind(Day07Puzzle::parse("33333")));
	}

	TEST_CASE("Day 7 isFourOfAKind works", "[2023][Day07]")
	{
		REQUIRE_FALSE(Day07Puzzle::isFiveOfAKind(Day07Puzzle::parse("5AAAA")));
		REQUIRE_FALSE(Day07Puzzle::isFiveOfAKind(Day07Puzzle::parse("K5KKK")));
		REQUIRE_FALSE(Day07Puzzle::isFiveOfAKind(Day07Puzzle::parse("22522")));
		REQUIRE_FALSE(Day07Puzzle::isFiveOfAKind(Day07Puzzle::parse("TTT5T")));
		REQUIRE_FALSE(Day07Puzzle::isFiveOfAKind(Day07Puzzle::parse("33335")));

		REQUIRE(Day07Puzzle::isFourOfAKind(Day07Puzzle::parse("5AAAA")));
		REQUIRE(Day07Puzzle::isFourOfAKind(Day07Puzzle::parse("K5KKK")));
		REQUIRE(Day07Puzzle::isFourOfAKind(Day07Puzzle::parse("22522")));
		REQUIRE(Day07Puzzle::isFourOfAKind(Day07Puzzle::parse("TTT5T")));
		REQUIRE(Day07Puzzle::isFourOfAKind(Day07Puzzle::parse("33335")));
	}

	TEST_CASE("Day 7 isThreeOfAKind works", "[2023][Day07]")
	{
		REQUIRE(Day07Puzzle::isThreeOfAKind(Day07Puzzle::parse("53AAA")));
		REQUIRE(Day07Puzzle::isThreeOfAKind(Day07Puzzle::parse("5A3AA")));
		REQUIRE(Day07Puzzle::isThreeOfAKind(Day07Puzzle::parse("5AA3A")));
		REQUIRE(Day07Puzzle::isThreeOfAKind(Day07Puzzle::parse("5AAA3")));
		REQUIRE(Day07Puzzle::isThreeOfAKind(Day07Puzzle::parse("A35AA")));
		REQUIRE(Day07Puzzle::isThreeOfAKind(Day07Puzzle::parse("AA53A")));
		REQUIRE(Day07Puzzle::isThreeOfAKind(Day07Puzzle::parse("AAA35")));

		REQUIRE_FALSE(Day07Puzzle::isFullHouse(Day07Puzzle::parse("53AAA")));
		REQUIRE_FALSE(Day07Puzzle::isFullHouse(Day07Puzzle::parse("5A3AA")));
		REQUIRE_FALSE(Day07Puzzle::isFullHouse(Day07Puzzle::parse("5AA3A")));
		REQUIRE_FALSE(Day07Puzzle::isFullHouse(Day07Puzzle::parse("5AAA3")));
		REQUIRE_FALSE(Day07Puzzle::isFullHouse(Day07Puzzle::parse("A35AA")));
		REQUIRE_FALSE(Day07Puzzle::isFullHouse(Day07Puzzle::parse("AA53A")));
		REQUIRE_FALSE(Day07Puzzle::isFullHouse(Day07Puzzle::parse("AAA35")));
	}

	TEST_CASE("Day 7 isFullHouse works", "[2023][Day07]")
	{
		REQUIRE(Day07Puzzle::isFullHouse(Day07Puzzle::parse("55AAA")));
		REQUIRE(Day07Puzzle::isFullHouse(Day07Puzzle::parse("5A5AA")));
		REQUIRE(Day07Puzzle::isFullHouse(Day07Puzzle::parse("5AA5A")));
		REQUIRE(Day07Puzzle::isFullHouse(Day07Puzzle::parse("5AAA5")));
		REQUIRE(Day07Puzzle::isFullHouse(Day07Puzzle::parse("A55AA")));
		REQUIRE(Day07Puzzle::isFullHouse(Day07Puzzle::parse("AA55A")));
		REQUIRE(Day07Puzzle::isFullHouse(Day07Puzzle::parse("AAA55")));

		REQUIRE_FALSE(Day07Puzzle::isThreeOfAKind(Day07Puzzle::parse("55AAA")));
		REQUIRE_FALSE(Day07Puzzle::isThreeOfAKind(Day07Puzzle::parse("5A5AA")));
		REQUIRE_FALSE(Day07Puzzle::isThreeOfAKind(Day07Puzzle::parse("5AA5A")));
		REQUIRE_FALSE(Day07Puzzle::isThreeOfAKind(Day07Puzzle::parse("5AAA5")));
		REQUIRE_FALSE(Day07Puzzle::isThreeOfAKind(Day07Puzzle::parse("A55AA")));
		REQUIRE_FALSE(Day07Puzzle::isThreeOfAKind(Day07Puzzle::parse("AA55A")));
		REQUIRE_FALSE(Day07Puzzle::isThreeOfAKind(Day07Puzzle::parse("AAA55")));
	}

	TEST_CASE("Day 7 isTwoPair works", "[2023][Day07]")
	{
		REQUIRE(Day07Puzzle::isTwoPair(Day07Puzzle::parse("55AA4")));
		REQUIRE(Day07Puzzle::isTwoPair(Day07Puzzle::parse("545AA")));
		REQUIRE(Day07Puzzle::isTwoPair(Day07Puzzle::parse("5A45A")));
		REQUIRE(Day07Puzzle::isTwoPair(Day07Puzzle::parse("5A4A5")));
		REQUIRE(Day07Puzzle::isTwoPair(Day07Puzzle::parse("A55A4")));
		REQUIRE(Day07Puzzle::isTwoPair(Day07Puzzle::parse("4A55A")));
		REQUIRE(Day07Puzzle::isTwoPair(Day07Puzzle::parse("A4A55")));
	}

	TEST_CASE("Day 7 isOnePair works", "[2023][Day07]")
	{
		REQUIRE(Day07Puzzle::isOnePair(Day07Puzzle::parse("55JA4")));
		REQUIRE(Day07Puzzle::isOnePair(Day07Puzzle::parse("545JA")));
		REQUIRE(Day07Puzzle::isOnePair(Day07Puzzle::parse("5J45A")));
		REQUIRE(Day07Puzzle::isOnePair(Day07Puzzle::parse("5J4A5")));
		REQUIRE(Day07Puzzle::isOnePair(Day07Puzzle::parse("J55A4")));
		REQUIRE(Day07Puzzle::isOnePair(Day07Puzzle::parse("4A55J")));
		REQUIRE(Day07Puzzle::isOnePair(Day07Puzzle::parse("J4A55")));
	}

	TEST_CASE("Day 7 isHighCard works", "[2023][Day07]")
	{
		REQUIRE(Day07Puzzle::isHighCard(Day07Puzzle::parse("23456")));
		REQUIRE(Day07Puzzle::isHighCard(Day07Puzzle::parse("62345")));
		REQUIRE(Day07Puzzle::isHighCard(Day07Puzzle::parse("56234")));
	}

	TEST_CASE("Day 7 compareFiveOfAKind works", "[2023][Day07]")
	{
		REQUIRE(-1 == Day07Puzzle::compareFiveOfAKind(Day07Puzzle::parse("AAAAA"), Day07Puzzle::parse("33333")));
		REQUIRE(0 == Day07Puzzle::compareFiveOfAKind(Day07Puzzle::parse("33333"), Day07Puzzle::parse("33333")));
		REQUIRE(+1 == Day07Puzzle::compareFiveOfAKind(Day07Puzzle::parse("33333"), Day07Puzzle::parse("AAAAA")));
	}

	TEST_CASE("Day 7 compareFourOfAKind works", "[2023][Day07]")
	{
		REQUIRE(-1 == Day07Puzzle::compareFourOfAKind(Day07Puzzle::parse("AAAAK"), Day07Puzzle::parse("33334")));
		REQUIRE(-1 == Day07Puzzle::compareFourOfAKind(Day07Puzzle::parse("AAAAK"), Day07Puzzle::parse("AAAAQ")));
		REQUIRE(0 == Day07Puzzle::compareFourOfAKind(Day07Puzzle::parse("33233"), Day07Puzzle::parse("33233")));
		REQUIRE(+1 == Day07Puzzle::compareFourOfAKind(Day07Puzzle::parse("AAAAQ"), Day07Puzzle::parse("AAAAK")));
		REQUIRE(+1 == Day07Puzzle::compareFourOfAKind(Day07Puzzle::parse("33334"), Day07Puzzle::parse("AAAAK")));
	}

	TEST_CASE("Day 7 compareFullHouse works", "[2023][Day07]")
	{
		REQUIRE(-1 == Day07Puzzle::compareFullHouse(Day07Puzzle::parse("AAAKK"), Day07Puzzle::parse("33344")));
		REQUIRE(-1 == Day07Puzzle::compareFullHouse(Day07Puzzle::parse("AAAKK"), Day07Puzzle::parse("AAAQQ")));
		REQUIRE(0 == Day07Puzzle::compareFullHouse(Day07Puzzle::parse("33223"), Day07Puzzle::parse("32233")));
		REQUIRE(+1 == Day07Puzzle::compareFullHouse(Day07Puzzle::parse("AAAQQ"), Day07Puzzle::parse("AAAKK")));
		REQUIRE(+1 == Day07Puzzle::compareFullHouse(Day07Puzzle::parse("33344"), Day07Puzzle::parse("AAAKK")));
	}

	TEST_CASE("Day 7 compareThreeOfAKind works", "[2023][Day07]")
	{
		REQUIRE(-1 == Day07Puzzle::compareThreeOfAKind(Day07Puzzle::parse("AAAJK"), Day07Puzzle::parse("33345")));
		REQUIRE(-1 == Day07Puzzle::compareThreeOfAKind(Day07Puzzle::parse("AAAKJ"), Day07Puzzle::parse("AAAJQ")));
		REQUIRE(0 == Day07Puzzle::compareThreeOfAKind(Day07Puzzle::parse("33243"), Day07Puzzle::parse("32433")));
		REQUIRE(+1 == Day07Puzzle::compareThreeOfAKind(Day07Puzzle::parse("AAAJQ"), Day07Puzzle::parse("AAAKJ")));
		REQUIRE(+1 == Day07Puzzle::compareThreeOfAKind(Day07Puzzle::parse("33345"), Day07Puzzle::parse("AAAJK")));
	}

	TEST_CASE("Day 7 compareTwoPair works", "[2023][Day07]")
	{
		REQUIRE(-1 == Day07Puzzle::compareTwoPair(Day07Puzzle::parse("AAJJK"), Day07Puzzle::parse("33445")));
		REQUIRE(-1 == Day07Puzzle::compareTwoPair(Day07Puzzle::parse("AAQQK"), Day07Puzzle::parse("AAJJQ")));
		REQUIRE(-1 == Day07Puzzle::compareTwoPair(Day07Puzzle::parse("AAQQ5"), Day07Puzzle::parse("AAQQ4")));
		REQUIRE(0 == Day07Puzzle::compareTwoPair(Day07Puzzle::parse("32243"), Day07Puzzle::parse("32423")));
		REQUIRE(+1 == Day07Puzzle::compareTwoPair(Day07Puzzle::parse("AAQQ4"), Day07Puzzle::parse("AAQQ5")));
		REQUIRE(+1 == Day07Puzzle::compareTwoPair(Day07Puzzle::parse("AAJJQ"), Day07Puzzle::parse("AAQQK")));
		REQUIRE(+1 == Day07Puzzle::compareTwoPair(Day07Puzzle::parse("33445"), Day07Puzzle::parse("AAJJK")));
	}

	TEST_CASE("Day 7 compareOnePair works", "[2023][Day07]")
	{
		REQUIRE(-1 == Day07Puzzle::compareOnePair(Day07Puzzle::parse("55678"), Day07Puzzle::parse("22345")));
		REQUIRE(-1 == Day07Puzzle::compareOnePair(Day07Puzzle::parse("55678"), Day07Puzzle::parse("55342")));
		REQUIRE(-1 == Day07Puzzle::compareOnePair(Day07Puzzle::parse("55678"), Day07Puzzle::parse("55642")));
		REQUIRE(-1 == Day07Puzzle::compareOnePair(Day07Puzzle::parse("55678"), Day07Puzzle::parse("55672")));
		REQUIRE(0 == Day07Puzzle::compareOnePair(Day07Puzzle::parse("55678"), Day07Puzzle::parse("55678")));
		REQUIRE(+1 == Day07Puzzle::compareOnePair(Day07Puzzle::parse("55672"), Day07Puzzle::parse("55678")));
		REQUIRE(+1 == Day07Puzzle::compareOnePair(Day07Puzzle::parse("55642"), Day07Puzzle::parse("55678")));
		REQUIRE(+1 == Day07Puzzle::compareOnePair(Day07Puzzle::parse("55342"), Day07Puzzle::parse("55678")));
		REQUIRE(+1 == Day07Puzzle::compareOnePair(Day07Puzzle::parse("22345"), Day07Puzzle::parse("55678")));
	}

	TEST_CASE("Day 7 compareHighCard works", "[2023][Day07]")
	{
		REQUIRE(-1 == Day07Puzzle::compareHighCard(Day07Puzzle::parse("AKQJT"), Day07Puzzle::parse("76543")));
		REQUIRE(-1 == Day07Puzzle::compareHighCard(Day07Puzzle::parse("AKQJT"), Day07Puzzle::parse("A6543")));
		REQUIRE(-1 == Day07Puzzle::compareHighCard(Day07Puzzle::parse("AKQJT"), Day07Puzzle::parse("AK543")));
		REQUIRE(-1 == Day07Puzzle::compareHighCard(Day07Puzzle::parse("AKQJT"), Day07Puzzle::parse("AKQ43")));
		REQUIRE(-1 == Day07Puzzle::compareHighCard(Day07Puzzle::parse("AKQJT"), Day07Puzzle::parse("AKQJ3")));
		REQUIRE(+0 == Day07Puzzle::compareHighCard(Day07Puzzle::parse("AKQJT"), Day07Puzzle::parse("AKQJT")));
		REQUIRE(+1 == Day07Puzzle::compareHighCard(Day07Puzzle::parse("AKQJ3"), Day07Puzzle::parse("AKQJT")));
		REQUIRE(+1 == Day07Puzzle::compareHighCard(Day07Puzzle::parse("AKQ43"), Day07Puzzle::parse("AKQJT")));
		REQUIRE(+1 == Day07Puzzle::compareHighCard(Day07Puzzle::parse("AK543"), Day07Puzzle::parse("AKQJT")));
		REQUIRE(+1 == Day07Puzzle::compareHighCard(Day07Puzzle::parse("A6543"), Day07Puzzle::parse("AKQJT")));
		REQUIRE(+1 == Day07Puzzle::compareHighCard(Day07Puzzle::parse("76543"), Day07Puzzle::parse("AKQJT")));
	}

	TEST_CASE("Day 7 CompareHand works", "[2023][Day07]")
	{
		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("AAAAA"), Day07Puzzle::parse("33333")));
		REQUIRE(0 == Day07Puzzle::CompareHand(Day07Puzzle::parse("33333"), Day07Puzzle::parse("33333")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("33333"), Day07Puzzle::parse("AAAAA")));

		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("AAAAK"), Day07Puzzle::parse("33334")));
		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("AAAAK"), Day07Puzzle::parse("AAAAQ")));
		REQUIRE(0 == Day07Puzzle::CompareHand(Day07Puzzle::parse("33233"), Day07Puzzle::parse("33233")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("AAAAQ"), Day07Puzzle::parse("AAAAK")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("33334"), Day07Puzzle::parse("AAAAK")));

		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("AAAKK"), Day07Puzzle::parse("33344")));
		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("AAAKK"), Day07Puzzle::parse("AAAQQ")));
		REQUIRE(0 == Day07Puzzle::CompareHand(Day07Puzzle::parse("33223"), Day07Puzzle::parse("32233")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("AAAQQ"), Day07Puzzle::parse("AAAKK")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("33344"), Day07Puzzle::parse("AAAKK")));

		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("AAAJK"), Day07Puzzle::parse("33345")));
		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("AAAKJ"), Day07Puzzle::parse("AAAJQ")));
		REQUIRE(0 == Day07Puzzle::CompareHand(Day07Puzzle::parse("33243"), Day07Puzzle::parse("32433")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("AAAJQ"), Day07Puzzle::parse("AAAKJ")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("33345"), Day07Puzzle::parse("AAAJK")));

		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("AAJJK"), Day07Puzzle::parse("33445")));
		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("AAQQK"), Day07Puzzle::parse("AAJJQ")));
		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("AAQQ5"), Day07Puzzle::parse("AAQQ4")));
		REQUIRE(0 == Day07Puzzle::CompareHand(Day07Puzzle::parse("32243"), Day07Puzzle::parse("32423")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("AAQQ4"), Day07Puzzle::parse("AAQQ5")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("AAJJQ"), Day07Puzzle::parse("AAQQK")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("33445"), Day07Puzzle::parse("AAJJK")));

		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("55678"), Day07Puzzle::parse("22345")));
		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("55678"), Day07Puzzle::parse("55342")));
		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("55678"), Day07Puzzle::parse("55642")));
		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("55678"), Day07Puzzle::parse("55672")));
		REQUIRE(0 == Day07Puzzle::CompareHand(Day07Puzzle::parse("55678"), Day07Puzzle::parse("55678")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("55672"), Day07Puzzle::parse("55678")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("55642"), Day07Puzzle::parse("55678")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("55342"), Day07Puzzle::parse("55678")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("22345"), Day07Puzzle::parse("55678")));

		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("AKQJT"), Day07Puzzle::parse("76543")));
		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("AKQJT"), Day07Puzzle::parse("A6543")));
		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("AKQJT"), Day07Puzzle::parse("AK543")));
		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("AKQJT"), Day07Puzzle::parse("AKQ43")));
		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("AKQJT"), Day07Puzzle::parse("AKQJ3")));
		REQUIRE(+0 == Day07Puzzle::CompareHand(Day07Puzzle::parse("AKQJT"), Day07Puzzle::parse("AKQJT")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("AKQJ3"), Day07Puzzle::parse("AKQJT")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("AKQ43"), Day07Puzzle::parse("AKQJT")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("AK543"), Day07Puzzle::parse("AKQJT")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("A6543"), Day07Puzzle::parse("AKQJT")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("76543"), Day07Puzzle::parse("AKQJT")));
	}


	TEST_CASE("Day 7 CompareHand misc examples works", "[2023][Day07]")
	{
		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("T55J5"), Day07Puzzle::parse("32T3K")));
		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("KK677"), Day07Puzzle::parse("32T3K")));
		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("KTJJT"), Day07Puzzle::parse("32T3K")));
		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("QQQJA"), Day07Puzzle::parse("32T3K")));

		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("32T3K"), Day07Puzzle::parse("T55J5")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("32T3K"), Day07Puzzle::parse("KK677")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("32T3K"), Day07Puzzle::parse("KTJJT")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("32T3K"), Day07Puzzle::parse("QQQJA")));

		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("KK677"), Day07Puzzle::parse("KTJJT")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("KTJJT"), Day07Puzzle::parse("KK677")));

		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("T55J5"), Day07Puzzle::parse("KK677")));
		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("T55J5"), Day07Puzzle::parse("KTJJT")));
		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("QQQJA"), Day07Puzzle::parse("KK677")));
		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("QQQJA"), Day07Puzzle::parse("KTJJT")));

		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("KK677"), Day07Puzzle::parse("T55J5")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("KTJJT"), Day07Puzzle::parse("T55J5")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("KK677"), Day07Puzzle::parse("QQQJA")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("KTJJT"), Day07Puzzle::parse("QQQJA")));

		REQUIRE(-1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("QQQJA"), Day07Puzzle::parse("T55J5")));
		REQUIRE(+1 == Day07Puzzle::CompareHand(Day07Puzzle::parse("T55J5"), Day07Puzzle::parse("QQQJA")));
	}

	TEST_CASE("Day 7 Examples work", "[2023][Day07]") {
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
	}

}
