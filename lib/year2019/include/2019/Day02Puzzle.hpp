#ifndef INCLUDED_ADVENT_OF_CODE_2019_DAY_02_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2019_DAY_02_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentyNineteen {
	
	class Day02Puzzle : public core::PuzzleBase {
	public:
		Day02Puzzle();
		~Day02Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;
		std::pair<std::string, std::string> fastSolve(bool gravityAssistOn);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2019_DAY_02_PUZZLE_HPP_