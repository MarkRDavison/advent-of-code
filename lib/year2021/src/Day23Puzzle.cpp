#include <2021/Day23Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <zeno-engine/Core/Vector2.hpp>
#include <Core/Pathfinding.hpp>

namespace TwentyTwentyOne {

	template<typename T>
	struct vector2_hash_fxn {
		std::size_t operator()(const ze::Vector2<T>& _vec) const {
			return  std::hash<T>()(_vec.x) ^ std::hash<T>()(_vec.y);
		}
	};

	static AmphipodType extract(char _c) {
		if (_c == 'A') {
			return AmphipodType::A;
		}
		if (_c == 'B') {
			return AmphipodType::B;
		}
		if (_c == 'C') {
			return AmphipodType::C;
		}
		if (_c == 'D') {
			return AmphipodType::D;
		}
		throw std::runtime_error("Bad amphipod type.");
	}

	static char extract(AmphipodType _amph) {
		if (_amph == AmphipodType::A) {
			return 'A';
		}
		if (_amph == AmphipodType::B) {
			return 'B';
		}
		if (_amph == AmphipodType::C) {
			return 'C';
		}
		if (_amph == AmphipodType::D) {
			return 'D';
		}
		throw std::runtime_error("Bad amphipod type.");
	}

	Day23Puzzle::Day23Puzzle() :
		core::PuzzleBase("Amphipod", 2021, 23) {
	}


	void Day23Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day23Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day23Puzzle::fastSolve() {
		auto startingState = parse(m_InputLines);
		::internal::PriorityQueue<State, EnergyNumber> queue;
		queue.put(startingState, 0);

		std::unordered_set<std::string> visited;

		while (!queue.empty()) {
			auto current = queue.get();
			if (current.isFinalised()) {
				std::cout << "Found target" << std::endl;
				break;
			}

			auto hash = current.hash();
			if (visited.contains(hash)) {
				continue;
			}

			visited.insert(hash);

			//std::cout << "===================" << std::endl;
			//std::cout << "=     Current     =" << std::endl;
			std::cout << "Queue size: " << queue.elements.size() << " / visited size: " << visited.size() << std::endl;
			//std::cout << "===================" << std::endl;
			std::cout << hash << std::endl;

			{
				unsigned roomId = 0;
				//std::cout << "===================" << std::endl;
				//std::cout << "= Room -> Hallway =" << std::endl;
				//std::cout << "===================" << std::endl;
				for (auto& room : current.rooms) {
					if (room.isFinalised()) {
						continue;
					}

					auto door = (int)(extract(room.type) - 'A') * 2 + 2;

					std::vector<AmphipodType> roomContent;
					if (room.amphipods.size() > 1) {
						for (int i = 0; i < (int)room.amphipods.size() - 1; ++i) {
							roomContent.push_back(room.amphipods[i]);
						}
					}
					auto newRoom = Room(room.type, 2, roomContent);

					//std::cout << "=================" << std::endl;
					for (const auto& [space, distance] : current.hallway.getValidMoves(door))
					{
						auto amphipod = room.type;
						auto newState(current);
						newState.hallway.spaces[space] = amphipod;
						newState.rooms[roomId] = newRoom;
						newState.energy = current.energy + (distance + 1 + room.gap()) * getEnergyForAnphipod(extract(amphipod));

						auto hash = newState.hash();
						if (visited.contains(hash)) {
							continue;
						}
						//std::cout << hash << std::endl;
						queue.put(newState, distance);
					}

					roomId++;
				}
			}

			{
				int hallwayIndex = 0;
				//std::cout << "===================" << std::endl;
				//std::cout << "= Hallway -> Room =" << std::endl;
				//std::cout << "===================" << std::endl;
				for (auto amph : current.hallway.spaces) {
					if (!amph.has_value()) {
						continue;
					}
					auto amphipod = amph.value();

					auto doorIndex = (int)(extract(amphipod) - 'A');
					auto door = doorIndex * 2 + 2;
					auto room = current.rooms[doorIndex];

					if (current.hallway.isClear(hallwayIndex, door) &&
						room.canEnter()) {
						auto newRoom(room);
						newRoom.amphipods.push_back(amphipod);
						auto distance = std::abs(door - hallwayIndex);

						auto newState(current);
						newState.hallway.spaces[hallwayIndex].reset();
						newState.rooms[doorIndex] = newRoom;

						auto hash = newState.hash();
						if (visited.contains(hash)) {
							continue;
						}
						//std::cout << hash << std::endl;
						queue.put(newState, distance);
					}

					hallwayIndex++;
				}
			}
		}

		return { "Part 1", "Part 2" };
	}

	State Day23Puzzle::parse(const std::vector<std::string>& _inputLines) const {
		State state{};

		state.rooms.emplace_back(Room(AmphipodType::A, 2, {
				extract(_inputLines[2][3]),
				extract(_inputLines[3][3])
			}));

		state.rooms.emplace_back(Room(AmphipodType::B, 2, {
				extract(_inputLines[2][5]),
				extract(_inputLines[3][5])
			}));

		state.rooms.emplace_back(Room(AmphipodType::C, 2, {
				extract(_inputLines[2][7]),
				extract(_inputLines[3][7])
			}));

		state.rooms.emplace_back(Room(AmphipodType::D, 2, {
				extract(_inputLines[2][9]),
				extract(_inputLines[3][9])
			}));

		return state;
	}

	EnergyNumber Day23Puzzle::getEnergyForAnphipod(char _c) {
		return static_cast<EnergyNumber>(std::powl(10, ((int)_c - 'A')));
	}
}
