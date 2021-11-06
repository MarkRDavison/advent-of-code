#ifndef INCLUDED_ADVENT_OF_CODE_2020_DAY_14_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2020_DAY_14_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <unordered_map>

namespace TwentyTwenty {

	using Day14Number = long long;

	struct Day14Struct {
		std::string mask;
		std::vector<std::pair<Day14Number, Day14Number>> mem;
	};
	
	class Day14Puzzle : public core::PuzzleBase {
	public:
		Day14Puzzle();
		~Day14Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::vector<Day14Struct> parse(const std::vector<std::string>& _inputLines);

		static std::string doPart1(const std::vector<Day14Struct>& _parsed);
		static std::string doPart2(const std::vector<Day14Struct>& _parsed);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2020_DAY_14_PUZZLE_HPP_