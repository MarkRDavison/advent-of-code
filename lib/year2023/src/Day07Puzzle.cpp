#include <2023/Day07Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <cassert>
#include <stdexcept>
#include <algorithm>

namespace TwentyTwentyThree {
	
	Day07Puzzle::Day07Puzzle() :
		core::PuzzleBase("Camel Cards", 2023, 7) {
	}

	char GetHighestOccurenceHighestValueCard(std::unordered_map<char, int> occ)
	{
		if (occ.contains('J'))
		{
			occ.erase('J');
		}
		const auto m = std::max_element(
			occ.begin(),
			occ.end(),
			[](const auto& lhs, const auto& rhs) -> bool
			{
				if (lhs.second == rhs.second)
				{
					return lhs.first < rhs.first;
				}

				return lhs.second < rhs.second;
			}
		);

		return (*m).first;
	}

	char GetFromOccurrenceByCount(const std::unordered_map<char, int>& occ, int c)
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

	char GetFromNthOccurrenceByCount(const std::unordered_map<char, int>& occ, int c, int occurence)
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

	int Day07Puzzle::CompareCardByOrder(const CamelCardHand& lhs, const CamelCardHand& rhs, bool jokers)
	{
		const std::unordered_map<char, int> part1Map = {
			{'2', 1},
			{'3', 2},
			{'4', 3},
			{'5', 4},
			{'6', 5},
			{'7', 6},
			{'8', 7},
			{'9', 8},
			{'T', 9},
			{'J', 10},
			{'Q', 11},
			{'K', 12},
			{'A', 13},
		};

		const std::unordered_map<char, int> part2Map = {
			{'2', 1},
			{'3', 2},
			{'4', 3},
			{'5', 4},
			{'6', 5},
			{'7', 6},
			{'8', 7},
			{'9', 8},
			{'T', 9},
			{'J', 0},
			{'Q', 11},
			{'K', 12},
			{'A', 13},
		};

		for (std::size_t i = 0; i < 5; ++i)
		{
			if (lhs[i] != rhs[i])
			{
				if (!jokers)
				{
					return part1Map.at(lhs[i]) > part1Map.at(rhs[i]) ? -1 : +1;
				}
				else
				{
					return part2Map.at(lhs[i]) > part2Map.at(rhs[i]) ? -1 : +1;
				}
			}
		}

		return 0;
	}

	int Day07Puzzle::CompareHand(const CamelCardHand& lhs, const CamelCardHand& rhs, bool jokers)
	{
		const bool lhsFiveOfAKind = isFiveOfAKind(lhs, jokers);
		const bool rhsFiveOfAKind = isFiveOfAKind(rhs, jokers);
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
			return CompareCardByOrder(lhs, rhs, jokers);
		}

		const bool lhsFourOfAKind = isFourOfAKind(lhs, jokers);
		const bool rhsFourOfAKind = isFourOfAKind(rhs, jokers);
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
			return CompareCardByOrder(lhs, rhs, jokers);
		}

		const bool lhsFullHouse = isFullHouse(lhs, jokers);
		const bool rhsFullHouse = isFullHouse(rhs, jokers);
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
			return CompareCardByOrder(lhs, rhs, jokers);
		}

		const bool lhsThreeOfAKind = isThreeOfAKind(lhs, jokers);
		const bool rhsThreeOfAKind = isThreeOfAKind(rhs, jokers);
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
			return CompareCardByOrder(lhs, rhs, jokers);
		}

		const bool lhsTwoPair = isTwoPair(lhs, jokers);
		const bool rhsTwoPair = isTwoPair(rhs, jokers);
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
			return CompareCardByOrder(lhs, rhs, jokers);
		}

		const bool lhsOnePair = isOnePair(lhs, jokers);
		const bool rhsOnePair = isOnePair(rhs, jokers);
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
			return CompareCardByOrder(lhs, rhs, jokers);
		}

		const bool lhsHighCard = isHighCard(lhs, jokers);
		const bool rhsHighCard = isHighCard(rhs, jokers);
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
			return CompareCardByOrder(lhs, rhs, jokers);
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
		CamelCardHand hand = "AAAAA";

		for (std::size_t i = 0; i < 5; ++i)
		{
			switch (str[i])
			{
				case '2':
				{
					hand[i] = '2';
					break;
				}
				case '3':
				{
					hand[i] = '3';
					break;
				}
				case '4':
				{
					hand[i] = '4';
					break;
				}
				case '5':
				{
					hand[i] = '5';
					break;
				}
				case '6':
				{
					hand[i] = '6';
					break;
				}
				case '7':
				{
					hand[i] = '7';
					break;
				}
				case '8':
				{
					hand[i] = '8';
					break;
				}
				case '9':
				{
					hand[i] = '9';
					break;
				}
				case 'T':
				{
					hand[i] = 'T';
					break;
				}
				case 'J':
				{
					hand[i] = 'J';
					break;
				}
				case 'Q':
				{
					hand[i] = 'Q';
					break;
				}
				case 'K':
				{
					hand[i] = 'K';
					break;
				}
				case 'A':
				{
					hand[i] = 'A';
					break;
				}
				default:
					throw std::runtime_error("Invalid character");
			}
		}

		return hand;
	}

	std::unordered_map<char, int> Day07Puzzle::GetCardOccurence(const CamelCardHand& hand)
	{
		std::unordered_map<char, int> occ;

		for (const auto& c : hand)
		{
			occ[c]++;
		}

		return occ;
	}

	std::unordered_map<char, int> GetJokerisedOccurences(const std::unordered_map<char, int>& occ)
	{
		auto jokerOccurence = occ;
		if (jokerOccurence.contains('J'))
		{
			const auto jokerCount = jokerOccurence.at('J');
			if (jokerCount == 5)
			{
				return { {'A',5} };
			}
			const auto toReplace = GetHighestOccurenceHighestValueCard(occ);
			jokerOccurence[toReplace] += jokerCount;
			jokerOccurence.erase('J');

		}
		return jokerOccurence;
	}

	bool isFiveOfAKindInternal(const std::unordered_map<char, int>& occ)
	{
		return occ.size() == 1 && (*occ.begin()).second == 5;
	}

	bool Day07Puzzle::isFiveOfAKind(const CamelCardHand& hand, bool jokers) {
		const auto& occ = GetCardOccurence(hand);

		if (jokers)
		{
			return isFiveOfAKindInternal(GetJokerisedOccurences(occ));
		}

		return isFiveOfAKindInternal(occ);
	}

	bool isFourOfAKindInternal(const std::unordered_map<char, int>& occ)
	{
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
	bool Day07Puzzle::isFourOfAKind(const CamelCardHand& hand, bool jokers) {
		const auto& occ = GetCardOccurence(hand);

		if (jokers)
		{
			return isFourOfAKindInternal(GetJokerisedOccurences(occ));
		}

		return isFourOfAKindInternal(occ);
	}

	bool isFullHouseInternal(const std::unordered_map<char, int>& occ)
	{
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
	bool Day07Puzzle::isFullHouse(const CamelCardHand& hand, bool jokers)
	{
		const auto& occ = GetCardOccurence(hand);

		if (jokers)
		{
			return isFullHouseInternal(GetJokerisedOccurences(occ));
		}

		return isFullHouseInternal(occ);
	}
	bool isThreeOfAKindInternal(const std::unordered_map<char, int>& occ)
	{
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
	bool Day07Puzzle::isThreeOfAKind(const CamelCardHand& hand, bool jokers)
	{
		const auto& occ = GetCardOccurence(hand);

		if (jokers)
		{
			return isThreeOfAKindInternal(GetJokerisedOccurences(occ));
		}

		return isThreeOfAKindInternal(occ);		
	}
	bool isTwoPairInternal(const std::unordered_map<char, int>& occ)
	{
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

		return twosFound == 2 && onesFound == 1;
	}
	bool Day07Puzzle::isTwoPair(const CamelCardHand& hand, bool jokers)
	{ 
		const auto& occ = GetCardOccurence(hand);

		if (jokers)
		{
			return isTwoPairInternal(GetJokerisedOccurences(occ));
		}

		return isTwoPairInternal(occ);
	}
	bool isOnePairInternal(const std::unordered_map<char, int>& occ)
	{
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
	bool Day07Puzzle::isOnePair(const CamelCardHand& hand, bool jokers)
	{
		const auto& occ = GetCardOccurence(hand);

		if (jokers)
		{
			return isOnePairInternal(GetJokerisedOccurences(occ));
		}

		return isOnePairInternal(occ);
	}
	bool isHighCardInternal(const std::unordered_map<char, int>& occ)
	{
		return occ.size() == 5;
	}
	bool Day07Puzzle::isHighCard(const CamelCardHand& hand, bool jokers)
	{
		const auto& occ = GetCardOccurence(hand);

		if (jokers)
		{
			return isHighCardInternal(GetJokerisedOccurences(occ));
		}

		return isHighCardInternal(occ);
	}

	struct HandBid
	{
		std::string strhand;
		CamelCardHand hand;
		long long bid;
	};

	long long part1(const std::vector<std::string>& m_InputLines)
	{
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
			hb.hand = Day07Puzzle::parse(parts[0]);
			hb.bid = std::stoll(parts[1]);
		}

		std::sort(
			handBids.begin(),
			handBids.end(),
			[](const HandBid& lhs, const HandBid& rhs) -> bool
			{
				return Day07Puzzle::CompareHand(lhs.hand, rhs.hand, false) == -1 ? false : true;
			});

		long long part1 = 0;

		for (std::size_t i = 1; i <= handBids.size(); ++i)
		{
			part1 += (long long)(i)*handBids[i - 1].bid;
		}

		return part1;
	}


	long long part2(const std::vector<std::string>& m_InputLines)
	{

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
			hb.hand = Day07Puzzle::parse(parts[0]);
			hb.bid = std::stoll(parts[1]);
		}

		std::sort(
			handBids.begin(),
			handBids.end(),
			[](const HandBid& lhs, const HandBid& rhs) -> bool
			{
				return Day07Puzzle::CompareHand(lhs.hand, rhs.hand, true) == -1 ? false : true;
			});

		long long part2 = 0;

		for (std::size_t i = 1; i <= handBids.size(); ++i)
		{
			part2 += (long long)(i)*handBids[i - 1].bid;
		}

		return part2;
	}

	std::pair<std::string, std::string> Day07Puzzle::fastSolve() {


		return { std::to_string(part1(m_InputLines)), std::to_string(part2(m_InputLines)) };
	}
}
