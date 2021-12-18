#ifndef INCLUDED_ADVENT_OF_CODE_2021_DAY_18_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2021_DAY_18_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyTwentyOne {

	using SnailFishDecimal = long;

	struct SnailFishNumber {

		enum class Type {
			Node,
			Leaf
		};

		Type type{ Type::Node };

		SnailFishDecimal depth{ 0 };
		SnailFishDecimal value{ 0 };
		SnailFishNumber* left{ nullptr };
		SnailFishNumber* right{ nullptr };
		SnailFishNumber* parent{ nullptr };

		std::string render() const;

	};
	
	class Day18Puzzle : public core::PuzzleBase {
	public:
		Day18Puzzle();
		~Day18Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static SnailFishNumber *parse(const std::string& _input);
		static SnailFishNumber* add(SnailFishNumber *_lhs, SnailFishNumber *_rhs);
		static std::pair<bool, SnailFishNumber*> explode(SnailFishNumber* _number);
		static std::pair<bool, SnailFishNumber*> split(SnailFishNumber* _number);
		static SnailFishDecimal magnitude(SnailFishNumber* _number);

		static SnailFishNumber* reduce(SnailFishNumber* _number);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2021_DAY_18_PUZZLE_HPP_