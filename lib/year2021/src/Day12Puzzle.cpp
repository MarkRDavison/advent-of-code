#include <2021/Day12Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <cassert>

namespace TwentyTwentyOne {
	
	Day12Puzzle::Day12Puzzle() :
		core::PuzzleBase("Passage Pathing", 2021, 12) {
	}


	void Day12Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day12Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	bool isSmall(const std::string& _node) {
		if (_node == "start" || _node == "end") {
			return false;
		}

		for (const auto c : _node) {
			if ('a' > c && c < 'z') {
				return false;
			}
		}

		return true;
	}

	PathResult recursiveVisit(const CaveConnections& _connections, Path _currentPath, std::string _special) {
		PathResult res{};
		for (const auto& next : _connections.at(_currentPath.current)) {
			auto special(_special);
			if (next == "start") {
				continue;
			}

			if (isSmall(next) && _currentPath.visitedSmall.count(next) > 0) {
				if (!special.empty() && next == special) {
					special = "";
				}
				else {
					continue;
				}
			}


			if (next == "end") {
				res.append(_currentPath.visited);
				continue;
			}
			
			auto newPath = Path(_currentPath);
			newPath.current = next;
			newPath.visited.push_back(next);
			if (isSmall(next)) {
				newPath.visitedSmall.insert({ next, false });
			}
			res.merge(recursiveVisit(_connections, newPath, special));
		}

		return res;
	}

	static PathResult visit(CaveConnections _connections, bool _part1) {
		const std::string START = "start";
		const std::string END = "end";
		std::string EMPTY = "";


		std::string node = START;

		auto p = Path{};
		p.current = START;
		p.visited.push_back(START);

		PathResult res{};

		res.merge(recursiveVisit(_connections, p, EMPTY));
		if (_part1) {
			return res;
		}

		for (const auto& [k, v] : _connections) {
			if (isSmall(k)) {
				res.merge(recursiveVisit(_connections, p, k));
			}
		}
		res.merge(recursiveVisit(_connections, p, EMPTY));

		return res;
	}

	std::pair<std::string, std::string> Day12Puzzle::fastSolve() {
		const auto connections = parse(m_InputLines);

		const auto part2 = visit(connections, false);
		const auto part1 = visit(connections, true);

		return { std::to_string(part1.visitedRoutes.size()), std::to_string(part2.visitedRoutes.size()) };
	}

	CaveConnections Day12Puzzle::parse(const std::vector<std::string>& _inputLines) {
		CaveConnections connectionInfo;
		for (const auto& s : _inputLines) {
			const auto& p = ze::StringExtensions::splitStringByDelimeter(s, "-");
			assert(p.size() == 2);

			connectionInfo[p[0]].insert(p[1]);
			connectionInfo[p[1]].insert(p[0]);
		}
		return connectionInfo;
	}
}
