#ifndef INCLUDED_ADVENT_OF_CODE_2020_DAY_21_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2020_DAY_21_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <set>

namespace TwentyTwenty {

	struct Day21Struct {
		std::set<std::string> ingredients;
		std::set<std::string> allergens;
	};

	using Day21Parsed = std::vector<Day21Struct>;
	
	class Day21Puzzle : public core::PuzzleBase {
	public:
		Day21Puzzle();
		~Day21Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static Day21Parsed parse(const std::vector<std::string>& _inputLines);
		static Day21Struct translate(const std::string& _str);

		static std::string doPart1(const Day21Parsed& _parsed);
		static std::string doPart2(const Day21Parsed& _parsed);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2020_DAY_21_PUZZLE_HPP_