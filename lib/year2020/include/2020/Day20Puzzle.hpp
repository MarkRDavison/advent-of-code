#ifndef INCLUDED_ADVENT_OF_CODE_2020_DAY_20_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2020_DAY_20_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyTwenty {

	struct Day20Struct {
		long id;
		std::vector<std::string> tiles;

	};

	using Parsed = std::vector<Day20Struct>;
	
	class Day20Puzzle : public core::PuzzleBase {
	public:
		Day20Puzzle();
		~Day20Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static Parsed parse(const std::vector<std::string>& _inputLines);

		static std::string doPart1(const Parsed& _parsed);
		static std::string doPart2(const Parsed& _parsed);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2020_DAY_20_PUZZLE_HPP_