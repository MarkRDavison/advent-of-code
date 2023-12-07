#ifndef INCLUDED_ADVENT_OF_CODE_2018_DAY_15_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2018_DAY_15_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <Core/Region.hpp>
#include <Core/Vector2.hpp>
#include <unordered_set>
#include <unordered_map>

namespace TwentyEighteen {

	struct BBUnit
	{
		char type{ '?' };
		Vector2i position;
		bool hasHadTurn{ false };
		int attackPower{ 3 };
		int hitPoints{ 200 };
	};

	struct FloodCaveCell
	{
		char c{ '#' };
		int distance{ -1 };
	};

	typedef std::vector<BBUnit> Units;
	typedef core::Region<char> Cave;
	typedef core::Region<FloodCaveCell> FloodCave;
	typedef std::unordered_set<Vector2i, Vector2_Hash_Fxn<int>> Vector2iSet;

	template <typename T>
	struct Vector2iMap
	{
		typedef std::unordered_map<Vector2i, T, Vector2_Hash_Fxn<int>> type;
	};

	struct BBUnitMovementInfo
	{
		Vector2iSet reachable;
		Vector2iSet nearest;
		Vector2i chosen;
		Vector2iSet nextMoves;
		Vector2i chosenNextMove;
	};
	
	class Day15Puzzle : public core::PuzzleBase {
	public:
		Day15Puzzle();
		~Day15Puzzle() override;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		static std::pair<Units, Cave> load(const std::vector<std::string>& input);
		static void resetUnitsForTurn(Units& units);
		static void sortUnitsForTurn(Units& units);		
		static void removeDeadUnits(Units& units);

		static Vector2iSet identifyTargetCells(const Cave& cave, const BBUnit& activeUnit, const Units& units);
		static Vector2iSet identifyDestinationCells(const Cave& cave, const BBUnit& activeUnit, const Units& units, const Vector2iSet& targetCells);
		static BBUnitMovementInfo identifyReachableAndNearestDestinationCells(const Cave& cave, const BBUnit& activeUnit, const Units& units, const Vector2iSet& destinationCells);

		static void identifyNextMove(const Cave& cave, const BBUnit& activeUnit, const Units& units, BBUnitMovementInfo& info);
		static void applyNextMove(BBUnit& activeUnit, const BBUnitMovementInfo& info);

		static void runMovementTurn(const Cave& cave, Units& units);
		static bool runMovementTurnForUnit(const Cave& cave, BBUnit& activeUnit, const Units& units);
		static void runAttackTurnForUnit(const Cave& cave, BBUnit& activeUnit, Units& units);

		static bool runFullRound(const Cave& cave, Units& units);

		static std::vector<std::string> printCaveToLines(const Cave& cave, const Units& units);
		static void printBeverageCave(const Cave& cave, const Units& units);
		static bool compareCaveToLives(const Cave& cave, const Units& units, const std::vector<std::string>& caveRepresentation);

		static int runToCompletion(const Cave& cave, Units& units);

		static std::string solvePart1(const Cave& cave, Units& units);
		static std::string solvePart2(const Cave& cave, const Units& units);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2018_DAY_15_PUZZLE_HPP_