#ifndef INCLUDED_ADVENT_OF_CODE_2023_DAY_07_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2023_DAY_07_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <array>
#include <unordered_map>

namespace TwentyTwentyThree {

	typedef std::string CamelCardHand;
	
	class Day07Puzzle : public core::PuzzleBase {
	public:
		Day07Puzzle();
		~Day07Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static int CompareHand(const CamelCardHand& lhs, const CamelCardHand& rhs, bool jokers);

		static int CompareCardByOrder(const CamelCardHand& lhs, const CamelCardHand& rhs, bool jokers);

		static std::unordered_map<char, int> GetCardOccurence(const CamelCardHand& hand);

		static bool isFiveOfAKind(const CamelCardHand& hand, bool jokers);
		static bool isFourOfAKind(const CamelCardHand& hand, bool jokers);
		static bool isFullHouse(const CamelCardHand& hand, bool jokers);
		static bool isThreeOfAKind(const CamelCardHand& hand, bool jokers);
		static bool isTwoPair(const CamelCardHand& hand, bool jokers);
		static bool isOnePair(const CamelCardHand& hand, bool jokers);
		static bool isHighCard(const CamelCardHand& hand, bool jokers);

		static CamelCardHand parse(const std::string& str);
	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2023_DAY_07_PUZZLE_HPP_