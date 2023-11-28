#include <2022/Day15Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Vector2.hpp>
#include <Core/Clock.hpp>
#include <Core/Region.hpp>
#include <unordered_map>
#include <cassert>

namespace TwentyTwentyTwo {
	template<typename T>
	struct vector2_hash_fxn_TODO_CORE_ME2 {
		std::size_t operator()(const Vector2<T>& _vec) const {
			return  std::hash<T>()(_vec.x) ^ std::hash<T>()(_vec.y);
		}
	};
	
	Day15Puzzle::Day15Puzzle() :
		core::PuzzleBase("Beacon Exclusion Zone", 2022, 15) {
	}


	void Day15Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day15Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	using SensorBeacons = std::unordered_map<Vector2i, Vector2i, vector2_hash_fxn_TODO_CORE_ME2<int>>;

	struct BeaconCell {
		char c{ '.' };
	};

	void applySensorInfoBeacon(core::Region<BeaconCell>& _region, const Vector2i& _sensor, const Vector2i& _beacon, int _targetRow)
	{
		const auto manhatten = std::abs(_sensor.x - _beacon.x) + std::abs(_sensor.y - _beacon.y);

		if (_sensor.y - manhatten <= _targetRow && _targetRow <= _sensor.y + manhatten)
		{
			for (int x = -manhatten; x <= +manhatten; ++x)
			{
				if (std::abs(x) + std::abs(_targetRow - _sensor.y) > manhatten) { continue; }
				auto& cell = _region.getCell(x + _sensor.x, _targetRow);
				if (cell.c == '.')
				{
					cell.c = '#';
				}
			}
		}

	}

	bool isValidDistressLocation(SensorBeacons& _sensorBeacons, const Vector2i& _possible)
	{
		bool possible = true;
		for (const auto& [sensor, beacon] : _sensorBeacons)
		{
			const auto manhattenClosest = std::abs(sensor.x - beacon.x) + std::abs(sensor.y - beacon.y);
			const auto manhattenTarget = std::abs(sensor.x - _possible.x) + std::abs(sensor.y - _possible.y);

			if (manhattenClosest >= manhattenTarget)
			{
				possible = false;
				break;
			}
		}
		return possible;
	}

	std::pair<std::string, std::string> Day15Puzzle::fastSolve() {
		return fastSolve(2000000, 4000000);
	}
	std::pair<std::string, std::string> Day15Puzzle::fastSolve(int _targetRow, int _maxDistressLocation)
	{
		SensorBeacons sensors;

		core::Region<BeaconCell> region;

		for (const auto& l : m_InputLines)
		{
			const auto& p = StringExtensions::splitStringByDelimeter(l, " =,:");

			const auto sensor = Vector2i(std::stoi(p[3]), std::stoi(p[5]));
			const auto beacon = Vector2i(std::stoi(p[11]), std::stoi(p[13]));

			region.getCell(sensor.x, sensor.y).c = 'S';
			region.getCell(beacon.x, beacon.y).c = 'B';

			sensors[sensor] = beacon;
		}

		for (const auto& [sensor, beacon] : sensors)
		{
			applySensorInfoBeacon(region, sensor, beacon, _targetRow);
		}

		int part1 = 0;

		for (int x = region.minX; x <= region.maxX; ++x)
		{
			const char cell = region.getCell(x, _targetRow).c;
			if (cell == '#')
			{
				part1++;
			}
		}

		const Vector2i minDistressLocation = { 0, 0 };
		const Vector2i maxDistressLocation = { _maxDistressLocation, _maxDistressLocation };

		Vector2i loc;
		bool found = false;

		for (const auto& [sensor, beacon] : sensors)
		{
			const auto manhattenPlus = std::abs(sensor.x - beacon.x) + std::abs(sensor.y - beacon.y) + 1;
			long long y = sensor.y-manhattenPlus;
			long long x = sensor.x;

			for (int i = 0; i < manhattenPlus; ++i)
			{
				y++;
				x++;
				if (x < minDistressLocation.x || y < minDistressLocation.y || x > maxDistressLocation.x || y > maxDistressLocation.y) { continue; }
				if (isValidDistressLocation(sensors, { (int)x, (int)y }))
				{
					return { std::to_string(part1), std::to_string(x * 4000000 + y) };
				}
			}

			for (int i = 0; i < manhattenPlus; ++i)
			{
				y++;
				x--;
				if (x < minDistressLocation.x || y < minDistressLocation.y || x > maxDistressLocation.x || y > maxDistressLocation.y) { continue; }
				if (isValidDistressLocation(sensors, { (int)x, (int)y }))
				{
					return { std::to_string(part1), std::to_string(x * 4000000 + y) };
				}
			}

			for (int i = 0; i < manhattenPlus; ++i)
			{
				y--;
				x--;
				if (x < minDistressLocation.x || y < minDistressLocation.y || x > maxDistressLocation.x || y > maxDistressLocation.y) { continue; }
				if (isValidDistressLocation(sensors, { (int)x, (int)y }))
				{
					return { std::to_string(part1), std::to_string(x * 4000000 + y) };
				}
			}

			for (int i = 0; i < manhattenPlus; ++i)
			{
				y--;
				x++;
				if (x < minDistressLocation.x || y < minDistressLocation.y || x > maxDistressLocation.x || y > maxDistressLocation.y) { continue; }
				if (isValidDistressLocation(sensors, { (int)x, (int)y }))
				{
					return { std::to_string(part1), std::to_string(x * 4000000 + y) };
				}
			}
		}

		return { std::to_string(part1), "Something went wrong......"};

	}
}
