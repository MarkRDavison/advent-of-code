#include <2020/Day24Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <zeno-engine/Core/Vector3.hpp>
#include <unordered_map>
#include <cassert>

namespace TwentyTwenty {

	template<typename T>
	struct vector3_hash_fxn {
		std::size_t operator()(const ze::Vector3<T>& _vec) const {
			return  std::hash<T>()(_vec.x) ^ std::hash<T>()(_vec.y) ^ std::hash<T>()(_vec.z);
		}
	};
	
	Day24Puzzle::Day24Puzzle() :
		core::PuzzleBase("Lobby Layout", 2020, 24) {
	}


	void Day24Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day24Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day24Puzzle::fastSolve() {
		using HexGrid = std::unordered_map<ze::Vector3i, bool, vector3_hash_fxn<int>>;
		int maxDistance = 0;
		HexGrid tiles;
		const std::unordered_map<std::string, ze::Vector3i> instructionsToDirections = {
			{ "e",  ze::Vector3i(+1, -1, +0) },
			{ "w",  ze::Vector3i(-1, +1, +0) },
			{ "se", ze::Vector3i(+0, -1, +1) },
			{ "ne", ze::Vector3i(+1, +0, -1) },
			{ "sw", ze::Vector3i(-1, +0, +1) },
			{ "nw", ze::Vector3i(+0, +1, -1) },
		};

		const auto circularInstructionOrderings = {
			"sw", "w", "nw", "ne", "e", "se"
		};

		std::vector<std::vector<std::string>> instructions;

		for (const auto& l : m_InputLines) {
			auto& row = instructions.emplace_back();
			for (unsigned i = 0; i < l.size(); ++i) {
				char c = l[i];
				if (c == 's' || c == 'n') {
					row.push_back(l.substr(i, 2));
					i++;
				}
				else {
					row.push_back(l.substr(i, 1));
				}
			}
		}

		for (const auto& i : instructions) {
			ze::Vector3i coords;
			for (const auto& instr : i) {
				coords += instructionsToDirections.at(instr);
			}
			tiles[coords] = !tiles[coords];
			maxDistance = std::max(maxDistance, std::max(std::abs(coords.x), std::max(std::abs(coords.y), std::abs(coords.z))));
		}


		const auto& countBlackTiles = [](const auto& _tiles) -> int {
			int blackTiles = 0;
			for (const auto& [coord, isBlack] : _tiles) {
				if (isBlack) {
					blackTiles++;
				}
			}
			return blackTiles;
		};

		const int part1 = countBlackTiles(tiles);

		const auto& countNeighbours = [&instructionsToDirections](const ze::Vector3i& _coords, const HexGrid& _tiles) -> int {
			int blackNeighbours = 0;

			for (const auto& [instr, offset] : instructionsToDirections) {
				const auto neighbourCoordinates = _coords + offset;
				if (_tiles.find(neighbourCoordinates) != _tiles.end()) {
					if (_tiles.at(neighbourCoordinates)) {
						blackNeighbours++;
					}
				}
			}

			return blackNeighbours;
		};

		const auto& getNextTileState = [&countNeighbours](const ze::Vector3i& _coords, const HexGrid& _tiles) -> bool {
			bool tileExists = _tiles.find(_coords) != _tiles.end();
			bool currentTile = tileExists ? _tiles.at(_coords) : false;
			bool nextTile = currentTile;
			int neighbours = countNeighbours(_coords, _tiles);
			if (currentTile) {
				if (neighbours == 0 || neighbours > 2) {
					nextTile = false;
				}
			} else {
				if (neighbours == 2) {
					nextTile = true;
				}
			}
			return nextTile;
		};

		const auto& flipTiles = 
			[&instructionsToDirections, &circularInstructionOrderings, &countNeighbours, &getNextTileState]
			(const HexGrid& _current, HexGrid& _next, int& _maxDistance) -> void {
				const int previousMaxDistance = _maxDistance;
				ze::Vector3i coordinates;

				_next[coordinates] = getNextTileState(coordinates, _current);

				for (int distance = 0; distance <= previousMaxDistance; ++distance) {
					coordinates = instructionsToDirections.at("e") * distance;
					for (const auto& instr : circularInstructionOrderings) {
						for (int circularDistance = 0; circularDistance < distance; ++circularDistance) {
							coordinates += instructionsToDirections.at(instr);
							_next[coordinates] = getNextTileState(coordinates, _current);
						}
					}
				}
			};

		HexGrid tilesSecond;

		HexGrid* current{ &tiles };
		HexGrid* next{ &tilesSecond };
		int part2 = 0;

		for (int i = 1; i <= 100; ++i) {
			maxDistance++;
			flipTiles(*current, *next, maxDistance);
			part2 = countBlackTiles(*next);
			std::cout << "Day " << i << ": " << part2 << std::endl;
			std::swap(current, next);
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
