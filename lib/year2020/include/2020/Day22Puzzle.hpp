#ifndef INCLUDED_ADVENT_OF_CODE_2020_DAY_22_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2020_DAY_22_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyTwenty {

	using Day22Number = long;

	struct Day22Struct {
		std::vector<Day22Number> player1;
		std::vector<Day22Number> player2;
	};
	
	class Day22Puzzle : public core::PuzzleBase {
	public:
		Day22Puzzle();
		~Day22Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static Day22Struct parse(const std::vector<std::string>& _inputLines);

		static std::string doPart1(const Day22Struct& _parsed);
		static std::string doPart2(const Day22Struct& _parsed);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2020_DAY_22_PUZZLE_HPP_