#include <2021/Day23Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Vector2.hpp>
#include <Core/Pathfinding.hpp>
#include <numeric>
#include <cassert>
#include <unordered_set>
#include <unordered_map>

namespace TwentyTwentyOne {

	EnergyNumber getEnergyForAnphipod(char _c) {
		return static_cast<EnergyNumber>(std::powl(10, ((int)_c - 'A')));
	}

	Day23Puzzle::Day23Puzzle() :
		core::PuzzleBase("Amphipod", 2021, 23) {
	}


	void Day23Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day23Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	Room::Room(char _amphipod, std::vector<char> _data) : owner(_amphipod), data(_data), size(_data.size()), fixed(0) {
		size -= std::ranges::count(data, '.');
		auto it = std::ranges::find_if_not(data, [_amphipod](char c) { return c == _amphipod; });
		fixed = it - data.begin();
	}

	bool Room::isFinished() const {
		return fixed == data.size();
	}

	bool Room::canAccept() const {
		return fixed == size && size != data.size();
	}

	bool Room::hasVisitors() const {
		return fixed != data.size() && fixed != size && size != 0;
	}

	char Room::top() const {
		assert(size != 0 && "Room is empty.");
		return data[size - 1];
	}

	EnergyNumber Room::pop() {
		assert(size != 0 && "Room is empty.");
		EnergyNumber cost = (data.size() - size + 1) * getEnergyForAnphipod(data[size - 1]);
		data[size - 1] = '.';
		size--;
		return cost;
	}

	EnergyNumber Room::push(char _amphipod) {
		assert(canAccept() && "Room cant take amphipod.");
		assert(_amphipod == owner && "Room cant take this amphipod.");

		EnergyNumber cost = (data.size() - size) * getEnergyForAnphipod(_amphipod);
		data[size] = _amphipod;
		size++;
		fixed++;
		return cost;
	}

	EnergyNumber distance(EnergyNumber _from, EnergyNumber _to) {
		if (_to > _from) {
			return _to - _from;
		}

		return _from - _to;
	}

	EnergyNumber Puzzle::optimalMoveToRoom() {
		for (EnergyNumber i = 0; i < hallway.size(); i++) {
			char amphipod = hallway[i];
			if (amphipod == '.') {
				continue;
			}

			if (!rooms[amphipod - 'A'].canAccept()) {
				continue;
			}

			EnergyNumber target = 2 + 2 * (amphipod - 'A');

			if (occupiedSpacesBetween(i, target) > 1) {
				continue;
			}

			EnergyNumber cost = rooms[amphipod - 'A'].push(amphipod);

			hallway[i] = '.';

			return cost + getEnergyForAnphipod(amphipod) * distance(i, target);
		}

		return 0;
	}

	EnergyNumber Puzzle::optimalRoomToRoom() {
		for (EnergyNumber h = 0; h < rooms.size(); h++) {

			if (!rooms[h].hasVisitors()) {
				continue;
			}

			char amphipod = rooms[h].top();

			if (!rooms[amphipod - 'A'].canAccept()) {
				continue;
			}

			if (occupiedSpacesBetween(2 * h + 2, 2 * (amphipod - 'A') + 2) != 0) {
				continue;
			}

			EnergyNumber cost = rooms[h].pop();

			cost += rooms[amphipod - 'A'].push(amphipod);
			cost += distance(h, amphipod - 'A') * 2 * getEnergyForAnphipod(amphipod);

			return cost;
		}

		return 0;
	}

	EnergyNumber Puzzle::occupiedSpacesBetween(EnergyNumber _from, EnergyNumber _to) const {
		auto b = hallway.begin() + std::min(_from, _to);
		auto e = hallway.begin() + std::max(_from, _to) + 1;

		return std::ranges::count_if(b, e, [](auto c) { return c != '.'; });
	}

	bool Puzzle::solved() const {
		for (auto& room : rooms) {
			if (!room.isFinished()) {
				return false;
			}
		}

		return true;
	}

	std::optional<EnergyNumber> Puzzle::hallwayMove(EnergyNumber _room, EnergyNumber _target) {
		// check the room
		if (!rooms[_room].hasVisitors()) {
			return {};
		}

		// don't land in front of rooms
		if (_target % 2 == 0 && _target != 0 && _target != 10) {
			return {};
		}

		EnergyNumber source = _room * 2 + 2;
		if (occupiedSpacesBetween(source, _target) != 0) {
			return {};
		}

		char amphipod = rooms[_room].top();
		EnergyNumber cost = distance(source, _target) * getEnergyForAnphipod(amphipod);
		cost += rooms[_room].pop();
		hallway[_target] = amphipod;

		return cost;
	}

	std::optional<EnergyNumber> findBestSolution(Puzzle& _puzzle) {
		EnergyNumber cost = 0;
		while (true) {
			EnergyNumber optimal = _puzzle.optimalMoveToRoom();

			optimal += _puzzle.optimalRoomToRoom();

			if (optimal == 0) {
				break;
			}

			cost += optimal;
		}

		if (_puzzle.solved()) {
			return cost;
		}

		EnergyNumber best = std::numeric_limits<EnergyNumber>::max();

		for (EnergyNumber h = 0; h < _puzzle.rooms.size(); h++) {
			if (!_puzzle.rooms[h].hasVisitors()) {
				continue;
			}

			for (EnergyNumber i = 0; i < _puzzle.hallway.size(); i++) {
				if (i % 2 == 0 && i != 0 && i != 10) {
					continue;
				}

				if (_puzzle.occupiedSpacesBetween(h * 2 + 2, i) != 0) {
					continue;
				}

				Puzzle copy = _puzzle;
				auto move_cost = copy.hallwayMove(h, i);

				if (!move_cost.has_value()) {
					continue;
				}

				auto recursion = findBestSolution(copy);

				if (!recursion.has_value()) {
					continue;
				}

				best = std::min(best, move_cost.value() + recursion.value());
			}
		}

		if (best == std::numeric_limits<EnergyNumber>::max()) {
			return {};
		}

		return best + cost;
	}

	std::pair<std::string, std::string> Day23Puzzle::fastSolve() {

		std::vector<char> hallway;
		for (unsigned i = 1; i <= 11; ++i) {
			hallway.push_back(m_InputLines[1][i]);
		}

		std::array<std::vector<char>, 4> rooms;

		for (std::size_t i = 3; i <= 9; i += 2) {
			auto targetI = (i - 3) / 2;
			for (std::size_t j = m_InputLines.size() - 2; j >= 2; --j) {
				rooms[targetI].push_back(m_InputLines[j][i]);
			}
		}

		Puzzle part1;
		part1.hallway = hallway;
		part1.rooms = {
			{'A', rooms[0]},
			{'B', rooms[1]},
			{'C', rooms[2]},
			{'D', rooms[3]}
		};
		
		rooms[0].insert(rooms[0].begin() + 1, 'D');
		rooms[0].insert(rooms[0].begin() + 1, 'D');

		rooms[1].insert(rooms[1].begin() + 1, 'C');
		rooms[1].insert(rooms[1].begin() + 1, 'B');

		rooms[2].insert(rooms[2].begin() + 1, 'B');
		rooms[2].insert(rooms[2].begin() + 1, 'A');

		rooms[3].insert(rooms[3].begin() + 1, 'A');
		rooms[3].insert(rooms[3].begin() + 1, 'C');

		Puzzle part2;
		part2.hallway = hallway;
		part2.rooms = {
			{'A', rooms[0]},
			{'B', rooms[1]},
			{'C', rooms[2]},
			{'D', rooms[3]}
		};

		auto part1Solution = findBestSolution(part1).value();
		auto part2Solution = findBestSolution(part2).value();

		return { std::to_string(part1Solution), std::to_string(part2Solution) };
	}

}
