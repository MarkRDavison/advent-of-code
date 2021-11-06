#ifndef INCLUDED_ADVENT_OF_CODE_2020_DAY_18_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2020_DAY_18_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyTwenty {

	using Day18Number = long;
	struct Day18Struct {
		enum class TokenType {
			Digit,
			Plus,
			Times,
			OpenBracket,
			CloseBracket,
			NotApplicable
		};

		using ParsedTokens = std::vector<std::pair<TokenType, Day18Number>>;

		ParsedTokens parsed;
	};
	
	class Day18Puzzle : public core::PuzzleBase {
	public:
		Day18Puzzle();
		~Day18Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::vector<Day18Struct> parse(const std::vector<std::string>& _inputLines);
		static Day18Struct translate(const std::string& _str);

		static std::string doPart1(const std::vector<Day18Struct>& _parsed);
		static std::string doPart2(const std::vector<Day18Struct>& _parsed);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2020_DAY_18_PUZZLE_HPP_