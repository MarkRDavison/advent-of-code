#ifndef INCLUDED_ADVENT_OF_CODE_2020_DAY_23_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2020_DAY_23_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyTwenty {

	using Day23Number = long;

	struct Day23Struct {
		std::string label;
	};

	using Day23Parsed = Day23Struct;
	
	class Day23Puzzle : public core::PuzzleBase {
	public:
		Day23Puzzle();
		~Day23Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static Day23Parsed parse(const std::vector<std::string>& _inputLines);

		static std::string doPart1(const Day23Parsed& _parsed, unsigned _moves);
		static std::string doPart2(const Day23Parsed& _parsed);
	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2020_DAY_23_PUZZLE_HPP_