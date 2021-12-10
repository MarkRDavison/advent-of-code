#ifndef INCLUDED_ADVENT_OF_CODE_2021_DAY_10_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2021_DAY_10_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <stack>

namespace TwentyTwentyOne {

	using ScoreNumber = long long;

	struct CorruptionResult {
		bool incomplete{ false };
		bool corrupt{ false };
		ScoreNumber score{ 0 };
		std::stack<char> openStack;
	};

	struct CompletionResult {
		std::string complete;
		ScoreNumber score;
	};
	
	class Day10Puzzle : public core::PuzzleBase {
	public:
		Day10Puzzle();
		~Day10Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static CorruptionResult isCorrupt(const std::string& _chunk);
		static CompletionResult complete(CorruptionResult _corruption, const std::string& _chunk);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2021_DAY_10_PUZZLE_HPP_