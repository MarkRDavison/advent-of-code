#ifndef INCLUDED_ADVENT_OF_CODE_2021_DAY_23_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2021_DAY_23_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <unordered_set>
#include <optional>
#include <array>

namespace TwentyTwentyOne {

	using EnergyNumber = std::size_t;

	struct Room {
		Room(char _amphipod, std::vector<char> _data);

		bool isFinished() const;
		bool canAccept() const;
		bool hasVisitors() const;
		char top() const;
		EnergyNumber pop();
		EnergyNumber push(char _amphipod);
		char at(EnergyNumber _index) const { return data[_index]; }

	private:
		char owner;
		std::vector<char> data;
		EnergyNumber size;
		EnergyNumber fixed;
	};

	struct Puzzle {
		std::vector<char> hallway;
		std::vector<Room> rooms;

		EnergyNumber optimalMoveToRoom();
		EnergyNumber optimalRoomToRoom();
		std::optional<EnergyNumber> hallwayMove(EnergyNumber _home, EnergyNumber _pos);
		EnergyNumber occupiedSpacesBetween(EnergyNumber _from, EnergyNumber _to) const;
		bool solved() const;
	};

	std::optional<EnergyNumber> findBestSolution(Puzzle& puzzle);

	class Day23Puzzle : public core::PuzzleBase {
	public:
		Day23Puzzle();
		~Day23Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2021_DAY_23_PUZZLE_HPP_