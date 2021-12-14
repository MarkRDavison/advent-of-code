#ifndef INCLUDED_ADVENT_OF_CODE_2021_DAY_14_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2021_DAY_14_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <unordered_map>

namespace TwentyTwentyOne {

	using PolymerTemplates = std::unordered_map<std::string, std::string>;

	
	class Day14Puzzle : public core::PuzzleBase {
	public:
		Day14Puzzle();
		~Day14Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::pair<std::string, PolymerTemplates> parse(const std::vector<std::string>& _inputLines);


	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2021_DAY_14_PUZZLE_HPP_