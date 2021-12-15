#include <2021/Day15Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <Core/Pathfinding.hpp>

namespace TwentyTwentyOne {
	
	Day15Puzzle::Day15Puzzle() :
		core::PuzzleBase("Chiton", 2021, 15) {
	}

	void Day15Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day15Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	CaveInteger solve(const std::vector<std::string>& _inputLines, unsigned _multiple) {
		CaveInteger answer = 0;
		core::CartesianNetwork<CaveCell> network;

		network.cg.cells.resize(_inputLines.size() * _multiple);

		const ze::Vector2u size(_inputLines.size(), _inputLines[0].size());


		for (unsigned y = 0; y < _inputLines.size(); ++y) {
			for (unsigned x = 0; x < _inputLines[y].size(); ++x) {

				for (unsigned repeatY = 0; repeatY < _multiple; ++repeatY) {
					network.cg.cells[y + size.y * repeatY].resize(size.x * _multiple);
					for (unsigned repeatX = 0; repeatX < _multiple; ++repeatX) {
						const auto offset = ze::Vector2u(size.x * repeatX, size.y * repeatY);

						auto& cell = network.cg.cells[y + size.y * repeatY][x + size.x * repeatX];
						cell.risk = (long long)(_inputLines[y][x] - '0') + repeatX + repeatY;
						while (cell.risk > 9) {
							cell.risk -= 9;
						}

					}
				}
			}
		}


		const auto& path = network.performAStarSearch(
			{ 0, 0 }, 
			{ (int)network.cg.cells[0].size() - 1, (int)network.cg.cells.size() - 1 }
		);

		for (const auto& p : path) {
			if (p == ze::Vector2i{ 0, 0 }) { continue; }
			answer += network.cg.cells[p.y][p.x].risk;
		}

		return answer;
	}

	std::pair<std::string, std::string> Day15Puzzle::fastSolve() {
		CaveInteger part1 = solve(m_InputLines, 1);
		CaveInteger part2 = solve(m_InputLines, 5);

		return { std::to_string(part1), std::to_string(part2) };
	}
}
