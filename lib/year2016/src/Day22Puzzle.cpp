#include <2016/Day22Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentySixteen {
	
	Day22Puzzle::Day22Puzzle() :
		core::PuzzleBase("Grid Computing", 2016, 22) {

	}
	Day22Puzzle::~Day22Puzzle() {

	}


	void Day22Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day22Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day22Puzzle::fastSolve() {
		auto [region, nodeLocs] = parse(m_InputLines);
		std::vector<Vector2i> locs;

		for (const auto& v : nodeLocs) {
			locs.push_back(v);
		}

		int part1 = 0;
		Vector2i hole = { -1,-1 };
		int lowestWall = region.maxX;

		for (unsigned i = 0; i < locs.size(); ++i) {
			for (unsigned j = i + 1; j < locs.size(); ++j) {
				const auto& node1 = region.getCell(locs[i].x, locs[i].y);
				const auto& node2 = region.getCell(locs[j].x, locs[j].y);

				if (node1.used == 0) {
					hole = { locs[i].x, locs[i].y };
				}

				if (viablePair(node1, node2) || viablePair(node2, node1)) {
					part1++;
				}
			}
		}


		if (hole == Vector2i{-1, -1}) {
			throw std::runtime_error("Could not find the expected empty node");
		}

		for (int y = region.minY; y <= region.maxY; ++y) {
			for (int x = region.minX; x <= region.maxX; ++x) {
				const auto& node = region.getCell(x, y);
				if (node.size > 100) {
					lowestWall = std::min(lowestWall, x);
				}
			}
		}

		int moveLeft = hole.x - lowestWall + 1;
		int moveUp = hole.y;
		int moveRight = (region.maxX - 1) - (lowestWall - 1);
		int moveToGoal = moveLeft + moveUp + moveRight;
		int part2 = 5 * (region.maxX - 1) + 1 + moveToGoal;


		return { std::to_string(part1), std::to_string(part2)};
	}
	
	std::pair<
		core::Region<Node>,
		std::unordered_set<Vector2i, vector2_hash_fxn<int>>
	> Day22Puzzle::parse(const std::vector<std::string>& _inputLines) {
		core::Region<Node> region;
		std::unordered_set<Vector2i, vector2_hash_fxn<int>> nodeLocs;

		for (const auto& l : _inputLines) {

			const auto& parts = StringExtensions::splitStringByDelimeter(l, " -T%-xy");
			if (parts.size() != 7) {
				continue;
			}

			int x = std::stoi(parts[1]);
			int y = std::stoi(parts[2]);

			nodeLocs.insert({ x, y });
			auto& node = region.getCell(x, y);
			node.x = x;
			node.y = y;
			node.size = std::stoi(parts[3]);
			node.used = std::stoi(parts[4]);
			node.avail = std::stoi(parts[5]);
			node.usePerc = std::stoi(parts[6]);

		}

		return { region, nodeLocs };
	}

	bool Day22Puzzle::viablePair(const Node& _lhs, const Node& _rhs) {
		if (_lhs.used == 0) { return false; }
		if (_lhs.x == _rhs.x && _lhs.y == _rhs.y) { return false; }
		return _rhs.avail >= _lhs.used;
	}
}
