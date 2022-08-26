#ifndef INCLUDED_ADVENT_OF_CODE_2021_DAY_23_PUZZLE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2021_DAY_23_PUZZLE_HPP_

#include <Core/PuzzleBase.hpp>
#include <unordered_set>
#include <optional>
#include <array>

namespace TwentyTwentyOne {

	using EnergyNumber = long;

	enum class AmphipodType {
		A = 'A', B = 'B', C = 'C', D = 'D'
	};

	struct Room {

		Room(AmphipodType _type, unsigned _size, std::vector<AmphipodType> _amphipods) :
			type(_type),
			size(_size),
			amphipods(_amphipods)
		{
		}

		bool isFinalised() {
			if (amphipods.size() != size) {
				return false;
			}

			for (auto amph : amphipods) {
				if (amph != type) {
					return false;
				}
			}
			return true;
		}

		bool canEnter() {
			if (amphipods.size() < size) {
				return false;
			}

			for (auto amph : amphipods) {
				if (amph != type) {
					return false;
				}
			}
			return true;
		}

		EnergyNumber gap() {
			return (EnergyNumber)(size - amphipods.size());
		}

		AmphipodType type;		
		unsigned size;
		std::vector<AmphipodType> amphipods;
	};

	struct Hallway {
		std::array<std::optional<AmphipodType>, 11> spaces;

		std::vector<std::pair<EnergyNumber, EnergyNumber>> getValidMoves(int _doorXCoordinate) {
			std::vector<std::pair<EnergyNumber, EnergyNumber>> moves;

			const std::unordered_set<int> doors { 2, 4, 6, 8 };

			for (int i = _doorXCoordinate - 1; i >= 0; i--) {
				if (doors.contains(i)) { continue; }
				if (spaces[i].has_value()) {
					break;
				}
				moves.emplace_back(i, std::abs(_doorXCoordinate - i));
			}

			for (int i = _doorXCoordinate + 1; i < 11; i++) {
				if (doors.contains(i)) { continue; }
				if (spaces[i].has_value()) {
					break;
				}
				moves.emplace_back(i, std::abs(_doorXCoordinate - i));
			}

			return moves;
		}

		bool isClear(int _start, int _stop) {

			int min;
			int max;
			if (_start < _stop) {
				min = _start + 1;
				max = _stop + 1;
			}
			else {
				min = _stop;
				max = _start;
			}

			for (int i = min; i <= max; ++i) {
				if (spaces[i].has_value()) {
					return false;
				}
			}

			return true;
		}
	};

	struct State {
		std::vector<Room> rooms;
		Hallway hallway;
		EnergyNumber energy{0};

		bool isFinalised() {

			for (auto r : rooms) {
				if (!r.isFinalised()) {
					return false;
				}
			}
			return true;
		}

		std::string hash() const {
			std::string hashValue = "";
			for (const auto& r : rooms) {
				int amphC = 0;
				for (const auto amph : r.amphipods) {
					hashValue += (char)amph;
					amphC++;
				}
				for (unsigned i = amphC; i < r.size; ++i) {
					hashValue += '.';
				}
				hashValue += "|";
			}
			for (auto c : hallway.spaces) {

				hashValue += c.has_value() ? (char)c.value() : '.';
			}
			//hashValue += "|" + std::to_string(energy);
			return hashValue;
		}
	};
	
	class Day23Puzzle : public core::PuzzleBase {
	public:
		Day23Puzzle();
		~Day23Puzzle() override = default;

		void initialise(const core::InitialisationInfo& _initialisationInfo) override;
		void setInputLines(const std::vector<std::string>& _inputLines);
		std::pair<std::string, std::string> fastSolve() override;

		State parse(const std::vector<std::string>& _inputLines) const;

		EnergyNumber getEnergyForAnphipod(char _c);

	private:
		std::vector<std::string> m_InputLines;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2021_DAY_23_PUZZLE_HPP_