#ifndef INCLUDED_ADVENT_OF_CODE_2018_DAY_16_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_DAY_16_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <2018/OpCodeComputer.hpp>
#include <unordered_set>

namespace TwentyEighteen {

	struct OpCodeScenario
	{
		std::array<OpCodeNumber, 4> before;
		OpCodeNumber opcodeNumber;
		OpCodeNumber a;
		OpCodeNumber b;
		OpCodeNumber c;
		std::array<OpCodeNumber, 4> after;
	};
	
	class Day16Puzzle : public core::PuzzleBase {
	public:
		Day16Puzzle();
		~Day16Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::unordered_set<OpCodeType> validOpCodeTypes(const OpCodeScenario& scenario);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2018_DAY_16_PUZZLE_HPP_