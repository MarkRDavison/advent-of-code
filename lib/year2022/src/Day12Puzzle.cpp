#include <2022/Day12Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Vector2.hpp>
#include <Core/Pathfinding.hpp>
#include <unordered_set>
#include <numeric>
#include <cassert>

namespace TwentyTwentyTwo {
	template<typename T>
	struct vector2_hash_fxn_TODO_CORE_ME {
		std::size_t operator()(const Vector2<T>& _vec) const {
			return  std::hash<T>()(_vec.x) ^ std::hash<T>()(_vec.y);
		}
	};
	
	Day12Puzzle::Day12Puzzle() :
		core::PuzzleBase("Hill Climbing Algorithm", 2022, 12) {
	}


	void Day12Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day12Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct HillCell {
		int height;
		char c;

		bool valid() {
			return true;
		}

		float costTo(const HillCell& _target) const {
			if (this->height + 1 < _target.height) {
				return std::numeric_limits<float>::max();
			}

			return 1.0f;
		}
	};

	std::pair<std::string, std::string> Day12Puzzle::fastSolve() {
		core::CartesianNetwork<HillCell> network;

		Vector2i start;
		Vector2i target;

		std::unordered_set<Vector2i, vector2_hash_fxn_TODO_CORE_ME<int>> possibleStartingPoints;

		network.cg.cells.resize(m_InputLines.size());

		for (std::size_t y = 0; y < m_InputLines.size(); ++y) {
			network.cg.cells[y].resize(m_InputLines[y].size());
			for (std::size_t x = 0; x < m_InputLines[y].size(); ++x) {
				char val = m_InputLines[y][x];

				if (val == 'S')
				{
					start = { (int)x, (int)y };
					val = 'a';
				}
				else if (val == 'E')
				{
					target = { (int)x, (int)y };
					val = 'z';
				}

				if (val == 'a')
				{
					possibleStartingPoints.insert(Vector2i(x, y));
				}

				auto& cell = network.cg.cells[y][x];

				cell.height = (int)(val - 'a');
				cell.c = val;
			}
		}

		const auto& path = network.performAStarSearch(start, target);
		std::vector<Vector2i> pathPart2;
		int minSize = path.size() - 1;

		for (auto starting : possibleStartingPoints)
		{
			const auto& alternatePath = network.performAStarSearch(starting, target);

			if (alternatePath.empty())
			{
				continue;
			}
			const auto newLength = alternatePath.size() - 1;

			if (minSize > newLength)
			{
				minSize = newLength;
				pathPart2 = alternatePath;
			}
		}

		return { std::to_string(path.size() - 1), std::to_string(minSize) };
	}
}
