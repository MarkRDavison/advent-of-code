#include <2016/Day24Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <Core/Pathfinding.hpp>
#include <Core/Region.hpp>

namespace TwentySixteen {
	
	Day24Puzzle::Day24Puzzle() :
		core::PuzzleBase("Air Duct Spelunking", 2016, 24) {

	}
	Day24Puzzle::~Day24Puzzle() {

	}


	void Day24Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day24Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day24Puzzle::fastSolve() {
		core::EdgeNetwork network;
		core::CartesianNetwork<DuctCell> cnet;

		core::Region<char> region;
		std::vector<std::pair<char, ze::Vector2i>> locationsPair;

		for (unsigned y = 0; y < m_InputLines.size(); ++y) {
			auto& rows = cnet.getCells().emplace_back();
			for (unsigned x = 0; x < m_InputLines[0].size(); ++x) {
				auto& cell = region.getCell(x, y);
				cell = m_InputLines[y][x];

				auto& cnetCell = rows.emplace_back();
				cnetCell.open = cell != '#';

				if ('0' <= cell && cell <= '9') {
					locationsPair.emplace_back(cell, ze::Vector2i(x, y));
				}
			}
		}

		for (unsigned i = 0; i < locationsPair.size(); ++i) {
			for (unsigned j = i + 1; j < locationsPair.size(); ++j) {
				const auto& path = cnet.performAStarSearch(locationsPair[i].second, locationsPair[j].second);
				
				network.addEdge(std::string(1, locationsPair[i].first), std::string(1, locationsPair[j].first), static_cast<float>(path.size() - 1));
				network.addEdge(std::string(1, locationsPair[j].first), std::string(1, locationsPair[i].first), static_cast<float>(path.size() - 1));
			}
		}

		const auto& part1 = network.getShortestPathVisitingAll("0");
		const auto& part2 = network.getShortestPathVisitingAllReturningToStart("0");

		return { std::to_string((int)part1.second), std::to_string((int)part2.second) };
	}
}
