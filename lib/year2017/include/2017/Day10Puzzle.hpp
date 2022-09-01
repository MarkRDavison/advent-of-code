#ifndef INCLUDED_ADVENT_OF_CODE_2017_DAY_10_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2017_DAY_10_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>

namespace TwentySeventeen {

	using HashNumber = int;
	
	class Day10Puzzle : public core::PuzzleBase {
	public:
		Day10Puzzle();
		~Day10Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;
		std::string fastSolve(std::size_t _maxSize, bool _ascii, const std::vector<HashNumber>& _additional);

		static std::string knotHash(const std::string& _input);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2017_DAY_10_PUZZLE_HPP_