#include <2017/Day03Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <zeno-engine/Core/Vector2.hpp>

namespace TwentySeventeen {
	
	Day03Puzzle::Day03Puzzle() :
		core::PuzzleBase("Spiral Memory", 2017, 3) {

	}
	Day03Puzzle::~Day03Puzzle() {

	}


	void Day03Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day03Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	int sumExistingNeighbours(core::Region<int>& _region, const ze::Vector2i& _loc) {
		int sum = 0;

		sum += _region.getCell(_loc.x - 1, _loc.y - 1);
		sum += _region.getCell(_loc.x + 0, _loc.y - 1);
		sum += _region.getCell(_loc.x + 1, _loc.y - 1);

		sum += _region.getCell(_loc.x - 1, _loc.y + 0);
		sum += _region.getCell(_loc.x + 0, _loc.y + 0);
		sum += _region.getCell(_loc.x + 1, _loc.y + 0);

		sum += _region.getCell(_loc.x - 1, _loc.y + 1);
		sum += _region.getCell(_loc.x + 0, _loc.y + 1);
		sum += _region.getCell(_loc.x + 1, _loc.y + 1);

		return sum;
	}

	std::pair<std::string, std::string> Day03Puzzle::fastSolve() {
		const int input = std::stoi(m_InputLines[0]);

		int part1 = 0;
		
		int i;
		for (i = 1; ; i += 2) {
			if (i * i >= input) {
				const auto ring = (i - 2) / 2;
				const auto known = (i - 2) * (i - 2);
				auto current = known;

				ze::Vector2i loc{ (i - 2) / 2, (i - 2) / 2 };

				current += 1;
				loc.x += 1;

				if (current == input) {
					part1 = std::abs(loc.x) + std::abs(loc.y);
				}

				const auto ringSize = (ring + 1) * 2;

				// moving up
				for (int j = 0; j < ringSize - 1; ++j) {
					current += 1;
					loc.y -= 1;

					if (current == input) {
						part1 = std::abs(loc.x) + std::abs(loc.y);
						break;
					}
				}

				// moving left
				for (int j = 0; j < ringSize; ++j) {
					current += 1;
					loc.x -= 1;

					if (current == input) {
						part1 = std::abs(loc.x) + std::abs(loc.y);
						break;
					}
				}

				// moving down
				for (int j = 0; j < ringSize; ++j) {
					current += 1;
					loc.y += 1;

					if (current == input) {
						part1 = std::abs(loc.x) + std::abs(loc.y);
						break;
					}
				}

				// moving right
				for (int j = 0; j < ringSize; ++j) {
					current += 1;
					loc.x += 1;

					if (current == input) {
						part1 = std::abs(loc.x) + std::abs(loc.y);
						break;
					}
				}

				break;
			}
		}

		core::Region<int> board;

		board.getCell(0, 0) = 1;

		int ringSize = 1;
		ze::Vector2i loc{ 1,-1 };
		while (true) {
			// Moving UP
			for (int i = 0; i <= ringSize; ++i) {
				loc.y += 1;
				auto newVal = sumExistingNeighbours(board, loc);
				board.getCell(loc.x, loc.y) = newVal;
				if (newVal > input) {
					return { std::to_string(part1), std::to_string(newVal) };
				}
			}

			// Moving LEFT
			for (int i = 0; i <= ringSize; ++i) {
				loc.x -= 1;
				auto newVal = sumExistingNeighbours(board, loc);
				board.getCell(loc.x, loc.y) = newVal;
				if (newVal > input) {
					return { std::to_string(part1), std::to_string(newVal) };
				}
			}

			// Moving DOWN
			for (int i = 0; i <= ringSize; ++i) {
				loc.y -= 1;
				auto newVal = sumExistingNeighbours(board, loc);
				board.getCell(loc.x, loc.y) = newVal;
				if (newVal > input) {
					return { std::to_string(part1), std::to_string(newVal) };
				}
			}

			// Moving RIGHT
			for (int i = 0; i <= ringSize; ++i) {
				loc.x += 1;
				auto newVal = sumExistingNeighbours(board, loc);
				board.getCell(loc.x, loc.y) = newVal;
				if (newVal > input) {
					return { std::to_string(part1), std::to_string(newVal) };
				}
			}

			ringSize += 2;
			loc += { 1, -1 };
		}
	}
}
