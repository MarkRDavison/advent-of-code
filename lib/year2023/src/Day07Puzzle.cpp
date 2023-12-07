#include <2023/Day07Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <cassert>
#include <stdexcept>
#include <algorithm>

namespace TwentyTwentyThree {
	
	Day07Puzzle::Day07Puzzle() :
		core::PuzzleBase("Camel Cards", 2023, 7) {
	}

	CamelCard GetFromOccurrenceByCount(const std::unordered_map<CamelCard, int>& occ, int c)
	{
		for (const auto& [card, count] : occ)
		{
			if (count == c)
			{
				return card;
			}
		}

		throw std::runtime_error("Expected count was not found");
	}

	CamelCard GetFromNthOccurrenceByCount(const std::unordered_map<CamelCard, int>& occ, int c, int occurence)
	{
		for (const auto& [card, count] : occ)
		{
			if (count == c && occurence-- == 0)
			{
				return card;
			}
		}

		throw std::runtime_error("Expected count was not found");
	}

	void Day07Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day07Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	int Day07Puzzle::CompareHand(const CamelCardHand& lhs, const CamelCardHand& rhs)
	{
		const bool lhsFiveOfAKind = isFiveOfAKind(lhs);
		const bool rhsFiveOfAKind = isFiveOfAKind(rhs);
		if (lhsFiveOfAKind && !rhsFiveOfAKind)
		{
			return -1;
		}
		if (!lhsFiveOfAKind && rhsFiveOfAKind)
		{
			return +1;
		}
		if (lhsFiveOfAKind && rhsFiveOfAKind)
		{
			return compareFiveOfAKind(lhs, rhs);
		}

		const bool lhsFourOfAKind = isFourOfAKind(lhs);
		const bool rhsFourOfAKind = isFourOfAKind(rhs);
		if (lhsFourOfAKind && !rhsFourOfAKind)
		{
			return -1;
		}
		if (!lhsFourOfAKind && rhsFourOfAKind)
		{
			return +1;
		}
		if (lhsFourOfAKind && rhsFourOfAKind)
		{
			return compareFourOfAKind(lhs, rhs);
		}

		const bool lhsFullHouse = isFullHouse(lhs);
		const bool rhsFullHouse = isFullHouse(rhs);
		if (lhsFullHouse && !rhsFullHouse)
		{
			return -1;
		}
		if (!lhsFullHouse && rhsFullHouse)
		{
			return +1;
		}
		if (lhsFullHouse && rhsFullHouse)
		{
			return compareFullHouse(lhs, rhs);
		}

		const bool lhsThreeOfAKind = isThreeOfAKind(lhs);
		const bool rhsThreeOfAKind = isThreeOfAKind(rhs);
		if (lhsThreeOfAKind && !rhsThreeOfAKind)
		{
			return -1;
		}
		if (!lhsThreeOfAKind && rhsThreeOfAKind)
		{
			return +1;
		}
		if (lhsThreeOfAKind && rhsThreeOfAKind)
		{
			return compareThreeOfAKind(lhs, rhs);
		}

		const bool lhsTwoPair = isTwoPair(lhs);
		const bool rhsTwoPair = isTwoPair(rhs);
		if (lhsTwoPair && !rhsTwoPair)
		{
			return -1;
		}
		if (!lhsTwoPair && rhsTwoPair)
		{
			return +1;
		}
		if (lhsTwoPair && rhsTwoPair)
		{
			return compareTwoPair(lhs, rhs);
		}

		const bool lhsOnePair = isOnePair(lhs);
		const bool rhsOnePair = isOnePair(rhs);
		if (lhsOnePair && !rhsOnePair)
		{
			return -1;
		}
		if (!lhsOnePair && rhsOnePair)
		{
			return +1;
		}
		if (lhsOnePair && rhsOnePair)
		{
			return compareOnePair(lhs, rhs);
		}

		const bool lhsHighCard = isHighCard(lhs);
		const bool rhsHighCard = isHighCard(rhs);
		if (lhsHighCard && !rhsHighCard)
		{
			return -1;
		}
		if (!lhsHighCard && rhsHighCard)
		{
			return +1;
		}
		if (lhsHighCard && rhsHighCard)
		{
			return compareHighCard(lhs, rhs);
		}

		throw std::runtime_error("Unhandled combination");
	}

	CamelCardHand Day07Puzzle::parse(const std::string& str)
	{
		if (str.size() != 5)
		{
			std::cout << "BAD STR HAND: " << str << std::endl;
		}
		assert(str.size() == 5);
		CamelCardHand hand = {
			CamelCard::_A,
			CamelCard::_A,
			CamelCard::_A,
			CamelCard::_A,
			CamelCard::_A
		};

		for (std::size_t i = 0; i < 5; ++i)
		{
			switch (str[i])
			{
				case '2':
				{
					hand[i] = CamelCard::_2;
					break;
				}
				case '3':
				{
					hand[i] = CamelCard::_3;
					break;
				}
				case '4':
				{
					hand[i] = CamelCard::_4;
					break;
				}
				case '5':
				{
					hand[i] = CamelCard::_5;
					break;
				}
				case '6':
				{
					hand[i] = CamelCard::_6;
					break;
				}
				case '7':
				{
					hand[i] = CamelCard::_7;
					break;
				}
				case '8':
				{
					hand[i] = CamelCard::_8;
					break;
				}
				case '9':
				{
					hand[i] = CamelCard::_9;
					break;
				}
				case 'T':
				{
					hand[i] = CamelCard::_T;
					break;
				}
				case 'J':
				{
					hand[i] = CamelCard::_J;
					break;
				}
				case 'Q':
				{
					hand[i] = CamelCard::_Q;
					break;
				}
				case 'K':
				{
					hand[i] = CamelCard::_K;
					break;
				}
				case 'A':
				{
					hand[i] = CamelCard::_A;
					break;
				}
				default:
					throw std::runtime_error("Invalid character");
			}
		}

		return hand;
	}

	std::unordered_map<CamelCard, int> Day07Puzzle::GetCardOccurence(const CamelCardHand& hand)
	{
		std::unordered_map<CamelCard, int> occ;

		for (const auto& c : hand)
		{
			occ[c]++;
		}

		return occ;
	}

	bool Day07Puzzle::isFiveOfAKind(const CamelCardHand& hand) {
		const auto& occ = GetCardOccurence(hand);

		return occ.size() == 1 && (*occ.begin()).second == 5;
	}
	bool Day07Puzzle::isFourOfAKind(const CamelCardHand& hand) {
		const auto& occ = GetCardOccurence(hand);

		if (occ.size() != 2)
		{
			return false;
		}

		bool fourFound = false;
		bool oneFound = false;

		for (const auto& [card, count] : occ)
		{
			if (count == 4)
			{
				fourFound = true;
			}
			else if (count == 1)
			{
				oneFound = true;
			}
		}

		return fourFound && oneFound;
	}
	bool Day07Puzzle::isFullHouse(const CamelCardHand& hand) 
	{
		const auto& occ = GetCardOccurence(hand);

		if (occ.size() != 2)
		{
			return false;
		}

		bool threeFound = false;
		bool twoFound = false;

		for (const auto& [card, count] : occ)
		{
			if (count == 3)
			{
				threeFound = true;
			}
			else if (count == 2)
			{
				twoFound = true;
			}
		}

		return threeFound && twoFound;
	}
	bool Day07Puzzle::isThreeOfAKind(const CamelCardHand& hand) 
	{
		const auto& occ = GetCardOccurence(hand);

		if (occ.size() != 3)
		{
			return false;
		}

		bool threeFound = false;
		int onesFound = 0;

		for (const auto& [card, count] : occ)
		{
			if (count == 3)
			{
				threeFound = true;
			}
			else if (count == 1)
			{
				onesFound++;
			}
		}

		return threeFound && onesFound == 2;
	}
	bool Day07Puzzle::isTwoPair(const CamelCardHand& hand) 
	{ 
		const auto& occ = GetCardOccurence(hand);

		if (occ.size() != 3)
		{
			return false;
		}

		int twosFound = 0;
		int onesFound = 0;

		for (const auto& [card, count] : occ)
		{
			if (count == 2)
			{
				twosFound++;
			}
			else if (count == 1)
			{
				onesFound++;
			}
		}

		return twosFound ==2 && onesFound == 1;
	}
	bool Day07Puzzle::isOnePair(const CamelCardHand& hand)
	{
		const auto& occ = GetCardOccurence(hand);

		if (occ.size() != 4)
		{
			return false;
		}

		int twosFound = 0;
		int onesFound = 0;

		for (const auto& [card, count] : occ)
		{
			if (count == 2)
			{
				twosFound++;
			}
			else if (count == 1)
			{
				onesFound++;
			}
		}

		return twosFound == 1 && onesFound == 3;
	}
	bool Day07Puzzle::isHighCard(const CamelCardHand& hand) 
	{
		const auto& occ = GetCardOccurence(hand);

		return occ.size() == 5;
	}

	int Day07Puzzle::compareFiveOfAKind(const CamelCardHand& lhs, const CamelCardHand& rhs) 
	{
		assert(isFiveOfAKind(lhs) && isFiveOfAKind(rhs));

		const auto& lhsOcc = GetCardOccurence(lhs);
		const auto& rhsOcc = GetCardOccurence(rhs);

		const auto lhsval = (int)(*lhsOcc.begin()).first;
		const auto rhsval = (int)(*rhsOcc.begin()).first;

		if (lhsval == rhsval) { return 0; }
		return lhsval > rhsval ? -1 : +1;
	}
	int Day07Puzzle::compareFourOfAKind(const CamelCardHand& lhs, const CamelCardHand& rhs) 
	{
		assert(isFourOfAKind(lhs) && isFourOfAKind(rhs));

		const auto& lhsOcc = GetCardOccurence(lhs);
		const auto& rhsOcc = GetCardOccurence(rhs);

		const auto& lhs4Card = GetFromOccurrenceByCount(lhsOcc, 4);
		const auto& lhs1Card = GetFromOccurrenceByCount(lhsOcc, 1);
		const auto& rhs4Card = GetFromOccurrenceByCount(rhsOcc, 4);
		const auto& rhs1Card = GetFromOccurrenceByCount(rhsOcc, 1);

		if (lhs4Card == rhs4Card)
		{
			if (lhs1Card == rhs1Card)
			{
				return 0;
			}

			return lhs1Card > rhs1Card ? -1 : +1;
		}

		return lhs4Card > rhs4Card ? -1 : +1;
	}
	int Day07Puzzle::compareFullHouse(const CamelCardHand& lhs, const CamelCardHand& rhs)
	{
		assert(isFullHouse(lhs) && isFullHouse(rhs));

		const auto& lhsOcc = GetCardOccurence(lhs);
		const auto& rhsOcc = GetCardOccurence(rhs);

		const auto& lhs3Card = GetFromOccurrenceByCount(lhsOcc, 3);
		const auto& lhs1Card = GetFromOccurrenceByCount(lhsOcc, 2);
		const auto& rhs3Card = GetFromOccurrenceByCount(rhsOcc, 3);
		const auto& rhs1Card = GetFromOccurrenceByCount(rhsOcc, 2);

		if (lhs3Card == rhs3Card)
		{
			if (lhs1Card == rhs1Card)
			{
				return 0;
			}

			return lhs1Card > rhs1Card ? -1 : +1;
		}

		return lhs3Card > rhs3Card ? -1 : +1;
	}
	int Day07Puzzle::compareThreeOfAKind(const CamelCardHand& lhs, const CamelCardHand& rhs)
	{
		assert(isThreeOfAKind(lhs) && isThreeOfAKind(rhs));

		const auto& lhsOcc = GetCardOccurence(lhs);
		const auto& rhsOcc = GetCardOccurence(rhs);

		const auto& lhs3Card = GetFromOccurrenceByCount(lhsOcc, 3);
		const auto& lhs1HighCard = GetFromNthOccurrenceByCount(lhsOcc, 1, 0);
		const auto& lhs1LowCard = GetFromNthOccurrenceByCount(lhsOcc, 1, 1);
		const auto& rhs3Card = GetFromOccurrenceByCount(rhsOcc, 3);
		const auto& rhs1HighCard = GetFromNthOccurrenceByCount(rhsOcc, 1, 0);
		const auto& rhs1LowCard = GetFromNthOccurrenceByCount(rhsOcc, 1, 1);

		if (lhs3Card == rhs3Card)
		{
			if (lhs1HighCard == rhs1HighCard)
			{
				if (lhs1LowCard == rhs1LowCard)
				{
					return 0;
				}

				return lhs1LowCard > rhs1LowCard ? -1 : +1;
			}

			return lhs1HighCard > rhs1HighCard ? -1 : +1;
		}

		return lhs3Card > rhs3Card ? -1 : +1;
	}

	int Day07Puzzle::compareTwoPair(const CamelCardHand& lhs, const CamelCardHand& rhs) 
	{
		assert(isTwoPair(lhs) && isTwoPair(rhs));

		const auto& lhsOcc = GetCardOccurence(lhs);
		const auto& rhsOcc = GetCardOccurence(rhs);

		const auto& lhsHighPairCard = GetFromNthOccurrenceByCount(lhsOcc, 2, 0);
		const auto& lhsLowPairCard = GetFromNthOccurrenceByCount(lhsOcc, 2, 1);
		const auto& lhs1LowCard = GetFromOccurrenceByCount(lhsOcc, 1);
		const auto& rhsHighPairCard = GetFromNthOccurrenceByCount(rhsOcc, 2, 0);
		const auto& rhsLowPairCard = GetFromNthOccurrenceByCount(rhsOcc, 2, 1);
		const auto& rhs1LowCard = GetFromOccurrenceByCount(rhsOcc, 1);

		if (lhsHighPairCard == rhsHighPairCard)
		{
			if (lhsLowPairCard == rhsLowPairCard)
			{
				if (lhs1LowCard == rhs1LowCard)
				{
					return 0;
				}

				return lhs1LowCard > rhs1LowCard ? -1 : +1;
			}

			return lhsLowPairCard > rhsLowPairCard ? -1 : +1;
		}

		return lhsHighPairCard > rhsHighPairCard ? -1 : +1;
	}
	int Day07Puzzle::compareOnePair(const CamelCardHand& lhs, const CamelCardHand& rhs)
	{
		assert(isOnePair(lhs) && isOnePair(rhs));

		const auto& lhsOcc = GetCardOccurence(lhs);
		const auto& rhsOcc = GetCardOccurence(rhs);

		const auto& lhsPairCard = GetFromOccurrenceByCount(lhsOcc, 2);
		const auto& lhsHigh1Card = GetFromNthOccurrenceByCount(lhsOcc, 1, 0);
		const auto& lhsMed1Card = GetFromNthOccurrenceByCount(lhsOcc, 1, 1);
		const auto& lhsLow1Card = GetFromNthOccurrenceByCount(lhsOcc, 1, 2);

		const auto& rhsPairCard = GetFromOccurrenceByCount(rhsOcc, 2);
		const auto& rhsHigh1Card = GetFromNthOccurrenceByCount(rhsOcc, 1, 0);
		const auto& rhsMed1Card = GetFromNthOccurrenceByCount(rhsOcc, 1, 1);
		const auto& rhsLow1Card = GetFromNthOccurrenceByCount(rhsOcc, 1, 2);

		if (lhsPairCard == rhsPairCard)
		{
			if (lhsHigh1Card == rhsHigh1Card)
			{
				if (lhsMed1Card == rhsMed1Card)
				{
					if (lhsLow1Card == rhsLow1Card)
					{
						return 0;
					}

					return lhsLow1Card > rhsLow1Card ? -1 : +1;
				}

				return lhsMed1Card > rhsMed1Card ? -1 : +1;
			}

			return lhsHigh1Card > rhsHigh1Card ? -1 : +1;
		}

		return lhsPairCard > rhsPairCard ? -1 : +1;
	}

	int Day07Puzzle::compareHighCard(const CamelCardHand& lhs, const CamelCardHand& rhs)
	{
		assert(isHighCard(lhs) && isHighCard(rhs));

		const auto& lhsOcc = GetCardOccurence(lhs);
		const auto& rhsOcc = GetCardOccurence(rhs);

		const auto& lhs0Card = GetFromNthOccurrenceByCount(lhsOcc, 1, 0);
		const auto& lhs1Card = GetFromNthOccurrenceByCount(lhsOcc, 1, 1);
		const auto& lhs2Card = GetFromNthOccurrenceByCount(lhsOcc, 1, 2);
		const auto& lhs3Card = GetFromNthOccurrenceByCount(lhsOcc, 1, 3);
		const auto& lhs4Card = GetFromNthOccurrenceByCount(lhsOcc, 1, 4);

		const auto& rhs0Card = GetFromNthOccurrenceByCount(rhsOcc, 1, 0);
		const auto& rhs1Card = GetFromNthOccurrenceByCount(rhsOcc, 1, 1);
		const auto& rhs2Card = GetFromNthOccurrenceByCount(rhsOcc, 1, 2);
		const auto& rhs3Card = GetFromNthOccurrenceByCount(rhsOcc, 1, 3);
		const auto& rhs4Card = GetFromNthOccurrenceByCount(rhsOcc, 1, 4);

		if (lhs0Card == rhs0Card)
		{
			if (lhs1Card == rhs1Card)
			{
				if (lhs2Card == rhs2Card)
				{
					if (lhs3Card == rhs3Card)
					{
						if (lhs4Card == rhs4Card)
						{
							return 0;
						}

						return lhs4Card > rhs4Card ? -1 : +1;
					}

					return lhs3Card > rhs3Card ? -1 : +1;
				}

				return lhs2Card > rhs2Card ? -1 : +1;
			}

			return lhs1Card > rhs1Card ? -1 : +1;
		}

		return lhs0Card > rhs0Card ? -1 : +1;
	}

	struct HandBid
	{
		std::string strhand;
		CamelCardHand hand;
		long long bid;
	};

	std::pair<std::string, std::string> Day07Puzzle::fastSolve() {

		std::vector<HandBid> handBids;

		for (const auto& l : m_InputLines)
		{
			if (l.empty()) { continue; }

			const auto& parts = StringExtensions::splitStringByDelimeter(l, " ");

			auto& hb = handBids.emplace_back();

			if (parts[0].size() != 5)
			{
				std::cout << "BAD HAND LINE: " << l << std::endl;
			}

			hb.strhand = parts[0];
			hb.hand = parse(parts[0]);
			hb.bid = std::stoll(parts[1]);
		}

		std::sort(
			handBids.begin(),
			handBids.end(),
			[](const HandBid& lhs, const HandBid& rhs) -> bool
			{
				return CompareHand(lhs.hand, rhs.hand) == -1 ? false : true;
			});

		long long part1 = 0;

		for (std::size_t i = 1; i <= handBids.size(); ++i)
		{
			part1 += (long long)(i)*handBids[i - 1].bid;			
			std::cout << handBids[i - 1].strhand << std::endl;
		}

		std::cout << "248310101 is too high" << std::endl;

		return { std::to_string(part1), "Part 2"};
	}
}
