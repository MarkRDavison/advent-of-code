#ifndef INCLUDED_ADVENT_OF_CODE_2023_DAY_07_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2023_DAY_07_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <array>
#include <unordered_map>

namespace TwentyTwentyThree {

	enum class CamelCard : int
	{
		_2 = 0,
		_3 = 1,
		_4 = 2,
		_5 = 3,
		_6 = 4,
		_7 = 5,
		_8 = 6,
		_9 = 7,
		_T = 8,
		_J = 9,
		_Q = 10,
		_K = 11,
		_A = 12
	};

	typedef std::array<CamelCard, 5> CamelCardHand;
	
	class Day07Puzzle : public core::PuzzleBase {
	public:
		Day07Puzzle();
		~Day07Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static int CompareHand(const CamelCardHand& lhs, const CamelCardHand& rhs);

		static std::unordered_map<CamelCard, int> GetCardOccurence(const CamelCardHand& hand);

		static bool isFiveOfAKind(const CamelCardHand& hand);
		static bool isFourOfAKind(const CamelCardHand& hand);
		static bool isFullHouse(const CamelCardHand& hand);
		static bool isThreeOfAKind(const CamelCardHand& hand);
		static bool isTwoPair(const CamelCardHand& hand);
		static bool isOnePair(const CamelCardHand& hand);
		static bool isHighCard(const CamelCardHand& hand);

		static int compareFiveOfAKind(const CamelCardHand& lhs, const CamelCardHand& rhs);
		static int compareFourOfAKind(const CamelCardHand& lhs, const CamelCardHand& rhs);
		static int compareFullHouse(const CamelCardHand& lhs, const CamelCardHand& rhs);
		static int compareThreeOfAKind(const CamelCardHand& lhs, const CamelCardHand& rhs);
		static int compareTwoPair(const CamelCardHand& lhs, const CamelCardHand& rhs);
		static int compareOnePair(const CamelCardHand& lhs, const CamelCardHand& rhs);
		static int compareHighCard(const CamelCardHand& lhs, const CamelCardHand& rhs);

		static CamelCardHand parse(const std::string& str);
	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2023_DAY_07_PUZZLE_HPP_