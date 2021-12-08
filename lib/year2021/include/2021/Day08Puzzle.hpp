#ifndef INCLUDED_ADVENT_OF_CODE_2021_DAY_08_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2021_DAY_08_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <unordered_map>
#include <unordered_set>

namespace TwentyTwentyOne {

	using SegmentData = std::unordered_map<int, std::unordered_set<char>>;
	struct SegmentInput {
		std::string signals[10];
		std::string output[4];
	};
	
	class Day08Puzzle : public core::PuzzleBase {
	public:
		Day08Puzzle();
		~Day08Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static const SegmentData DisplaySegmentData;

		static std::vector<SegmentInput> parseInput(const std::vector<std::string>& _inputLines);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2021_DAY_08_PUZZLE_HPP_