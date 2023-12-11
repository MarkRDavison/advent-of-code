#ifndef INCLUDED_ADVENT_OF_CODE_2023_DAY_10_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2023_DAY_10_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <Core/Region.hpp>
#include <unordered_set>
#include <unordered_map>
#include <Core/Vector2.hpp>

namespace TwentyTwentyThree {

	struct PipeMazeCell
	{
		char originalCharacter{ '.' };
		char c{ '.' };
		bool mainLoop{ false };
		bool confirmedCenter{ false };

		bool connectUp{ false };
		bool connectLeft{ false };
		bool connectRight{ false };
		bool connectDown{ false };
	};

	typedef core::Region<PipeMazeCell> PipeMaze;
	
	class Day10Puzzle : public core::PuzzleBase {
	public:
		Day10Puzzle();
		~Day10Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::pair<PipeMaze, Vector2i> load(const std::vector<std::string>& _inputLines);
		static std::vector<std::string> drawPipeMaze(const PipeMaze& maze);

		static std::string solvePart1(const PipeMaze& maze, const Vector2i& start);

	private:
		std::vector<std::string> m_InputLines;

		static std::unordered_set<char> connectsRight;
		static std::unordered_set<char> connectsLeft;
		static std::unordered_set<char> connectsUp;
		static std::unordered_set<char> connectsDown;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2023_DAY_10_PUZZLE_HPP_