#include <2021/Day09Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <limits>
#include <queue>

namespace TwentyTwentyOne {
	
	Day09Puzzle::Day09Puzzle() :
		core::PuzzleBase("Smoke Basin", 2021, 9) {
	}


	void Day09Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day09Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day09Puzzle::fastSolve() {
		auto heightMap = createHeightMap(m_InputLines);
		auto lowPoints = findLowPoints(heightMap);

		Number part1 = 0;

		std::vector<Number> basinSizes;

		for (const auto& lowPoint : lowPoints) {
			part1 += 1 + heightMap.getCell(lowPoint.x, lowPoint.y);
			const auto currentBasin = findBasinSize(heightMap, lowPoint);
			basinSizes.push_back(currentBasin);
		}

		std::sort(basinSizes.begin(), basinSizes.end());
		std::reverse(basinSizes.begin(), basinSizes.end());

		return { std::to_string(part1), std::to_string(basinSizes[0] * basinSizes[1] * basinSizes[2]) };
	}

	core::Region<Number> Day09Puzzle::createHeightMap(const std::vector<std::string>& _inputLines) {
		core::Region<Number> region;
		int y = 0;
		for (const auto& row : _inputLines) {
			int x = 0;
			for (const auto& cell : row) {
				auto& heightMapCell = region.getCell(x, y);
				heightMapCell = cell - '0';
				x++;
			}
			y++;
		}

		return region;
	}

	std::vector<Vector2<Number>> Day09Puzzle::findLowPoints(const core::Region<Number>& _region) {
		std::vector<Vector2<Number>> lowPoints;

		for (int y = _region.minY; y <= _region.maxY; ++y) {
			for (int x = _region.minX; x <= _region.maxX; ++x) {

				const auto localValue = _region.getCell(x, y);

				// UP
				Number upValue = std::numeric_limits<Number>::max();
				if (y > _region.minY) {
					upValue = _region.getCell(x, y - 1);
				}

				// DOWN
				Number downValue = std::numeric_limits<Number>::max();
				if (y + 1 <= _region.maxY) {
					downValue = _region.getCell(x, y + 1);
				}

				// LEFT
				Number leftValue = std::numeric_limits<Number>::max();
				if (x > _region.minX) {
					leftValue = _region.getCell(x - 1, y);
				}

				// RIGHT
				Number rightValue = std::numeric_limits<Number>::max();
				if (x + 1 <= _region.maxX) {
					rightValue = _region.getCell(x + 1, y);
				}

				if (localValue < upValue &&
					localValue < downValue &&
					localValue < leftValue &&
					localValue < rightValue) {
					// LOWPOINT
					lowPoints.push_back({ x, y });
				}
			}
		}

		return lowPoints;
	}

	template<typename T>
	struct vector2_hash_fxn {
		std::size_t operator()(const Vector2<T>& _vec) const {
			return  std::hash<T>()(_vec.x) ^ std::hash<T>()(_vec.y);
		}
	};

	Number Day09Puzzle::findBasinSize(const core::Region<Number>& _region, const Vector2<Number>& _lowPoint) {

		std::unordered_set<Vector2<Number>, vector2_hash_fxn<Number>> visited;
		std::queue<Vector2<Number>> queue;
		queue.push(_lowPoint);

		Number basinSize = 0;

		while (!queue.empty()) {
			const auto current = queue.front();
			queue.pop();

			if (visited.count(current) != 0) {
				continue;
			}

			visited.insert(current);

			const auto currentValue = _region.getCell(current.x, current.y);

			if (currentValue >= 9) {
				continue;
			}
			basinSize++;
			// UP
			if (current.y > _region.minY) {
				queue.push({ current.x, current.y - 1 });
			}

			// DOWN
			if (current.y + 1 <= _region.maxY) {
				queue.push({ current.x, current.y + 1 });
			}

			// LEFT
			if (current.x > _region.minX) {
				queue.push({ current.x - 1, current.y });
			}

			// RIGHT
			if (current.x + 1 <= _region.maxX) {
				queue.push({ current.x + 1, current.y });
			}
		}

		return basinSize;
	}
}
