#include <2018/Day06Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Vector2.hpp>
#include <Core/Region.hpp>
#include <unordered_set>
#include <unordered_map>

namespace TwentyEighteen {
	
	Day06Puzzle::Day06Puzzle() :
		core::PuzzleBase("Chronal Coordinates", 2018, 6) {

	}
	Day06Puzzle::~Day06Puzzle() {

	}


	void Day06Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day06Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	void updateCell(core::Region<int>& _map, const std::vector<Vector2i>& _coords, int _x, int _y)
	{
		auto& cell = _map.getCell(_x, _y);
		if (cell == 0)
		{
			int closest = 0;
			int shared = 0;
			int distance = std::numeric_limits<int>::max();
			for (std::size_t i = 0; i < _coords.size(); ++i)
			{
				const auto manhatten = std::abs(_coords[i].x - _x) + std::abs(_coords[i].y - _y);
				if (manhatten == distance)
				{
					shared++;
				}
				else if (manhatten < distance)
				{
					distance = manhatten;
					closest = i;
					shared = 0;
				}
			}
			if (shared == 0)
			{
				cell = closest;
			}
			else
			{
				cell = 0;
			}
		}
	}

	std::size_t iterateMap(core::Region<int>& _map, const std::vector<Vector2i>& _coords)
	{
		std::size_t edgeDotCount = 0;
		int newMinY = _map.minY - 1;
		int newMaxY = _map.maxY + 1;
		int newMinX = _map.minX - 1;
		int newMaxX = _map.maxX + 1;

		for (int y = newMinY; y <= newMaxY; ++y)
		{
			for (int x = newMinX; x <= newMaxX; ++x)
			{
				if (x != newMinX && x != newMaxX && y != newMinY && y != newMaxY) continue;
				updateCell(_map, _coords, x, y);
				if (_map.getCell(x, y) == 0)
				{
					edgeDotCount++;
				}
			}
		}

		return edgeDotCount;
	}

	std::size_t calculateLargestNonInfinite(core::Region<int>& _map)
	{
		std::unordered_set<int> edgeValues;
		std::unordered_map<int, std::size_t> sizes;

		for (int y = _map.minY; y <= _map.maxY; ++y)
		{
			for (int x = _map.minX; x <= _map.maxX; ++x)
			{
				const auto cell = _map.getCell(x, y);
				sizes[cell]++;
				if (x != _map.minX && x != _map.maxX && y != _map.minY && y != _map.maxY) continue;

				edgeValues.insert(cell);
			}
		}

		std::size_t maxNonInfinite = 0;

		for (const auto& [val, size] : sizes)
		{
			if (edgeValues.contains(val))
			{
				continue;
			}

			maxNonInfinite = std::max(maxNonInfinite, size);
		}

		return maxNonInfinite;
	}

	std::size_t calculateWithinThresholdRegionSize(core::Region<int>& _map, const std::vector<Vector2i>& _coords, int _part2Threshold)
	{
		std::size_t answer = 0;


		for (int y = _map.minY; y <= _map.maxY; ++y)
		{
			for (int x = _map.minX; x <= _map.maxX; ++x)
			{
				int manhattenTotal = 0;
				for (std::size_t i = 0; i < _coords.size(); ++i)
				{
					const auto manhatten = std::abs(_coords[i].x - x) + std::abs(_coords[i].y - y);
					manhattenTotal += manhatten;
				}
				if (manhattenTotal < _part2Threshold)
				{
					answer++;
				}
			}
		}

		return answer;
	}

	std::pair<std::string, std::string> Day06Puzzle::fastSolve() {
		return fastSolve(10000);
	}
	
	std::pair<std::string, std::string> Day06Puzzle::fastSolve(int _part2Threshold)
	{
		std::vector<Vector2i> coords;

		core::Region<int> map;
		int offset = 1;

		for (const auto& i : m_InputLines)
		{
			const auto& p = StringExtensions::splitStringByDelimeter(i, " ,");

			auto& c = coords.emplace_back(Vector2i(std::stoi(p[0]), std::stoi(p[1])));
			map.getCell(c.x, c.y) = offset;
			offset++;
		}


		for (int y = map.minY; y <= map.maxY; ++y)
		{
			for (int x = map.minX; x <= map.maxX; ++x)
			{
				updateCell(map, coords, x, y);
			}
		}

		int i = 0;
		std::size_t edgeCount = 0;
		do
		{
			std::size_t currentEdge = edgeCount;
			edgeCount = iterateMap(map, coords);
		} while (i++ < (int)(std::sqrtf((float)_part2Threshold)));

		auto part1 = calculateLargestNonInfinite(map);
		auto part2 = calculateWithinThresholdRegionSize(map, coords, _part2Threshold);


		return { std::to_string(part1), std::to_string(part2) };
	}
}
