#include <2021/Day19Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <cassert>


namespace TwentyTwentyOne {

	Day19Puzzle::Day19Puzzle() :
		core::PuzzleBase("Beacon Scanner", 2021, 19) {
	}


	void Day19Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByLines(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0])));
	}

	void Day19Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day19Puzzle::fastSolve() {
		const auto& parsed = parse(m_InputLines);

		FixedBeaconData data;
		data.scanners[0] = {};

		for (const auto& beacon : parsed[0].beacons) {
			data.beacons.insert(beacon);
			data.beaconsFixedPerScanner[0].emplace_back(beacon);
		}

		while (data.scanners.size() != parsed.size()) {
			bool found = false;
			for (auto i = 0; i < parsed.size(); ++i) {
				if (found) {
					continue;
				}
				if (data.scanners.count(i) > 0) { continue; }

				for (auto j = 0; j < parsed.size(); ++j) {
					if (data.scanners.count(j) == 0) { continue; }
					std::cout << "Looking for scanner " << i << " (total " << data.scanners.size() << "/" << parsed.size() << ") " << " against scanner " << j << ", nodes: " << data.beacons.size() << std::endl;
					if (Day19Puzzle::areRelativelySame(
						i, 12, data, parsed[i].beacons, data.beaconsFixedPerScanner[j]
					)) {
						std::cout << "Found scanner " << i << ", now at " << data.scanners.size() << "/" << parsed.size() << std::endl;
						found = true;
						break;
					}
				}

			}
		}

		for (const auto& [k, v] : data.scanners) {
			std::cout << "Scanner " << k << ": " << v.x << "," << v.y << "," << v.z << std::endl;
		}

		BeaconDecimal part2 = 0;

		for (const auto& [k1, s1] : data.scanners) {
			for (const auto& [k2, s2] : data.scanners) {
				if (s1 == s2) { continue; }
				const auto manhatten = std::abs(s1.x - s2.x) + std::abs(s1.y - s2.y) + std::abs(s1.z - s2.z);
				part2 = std::max(part2, manhatten);
			}
		}

		return { std::to_string(data.beacons.size()), std::to_string(part2) };
	}

	std::vector<ParsedBeaconData> Day19Puzzle::parse(const std::vector<std::string>& _inputLines) {
		std::vector<ParsedBeaconData> parsed;
		parsed.push_back(ParsedBeaconData());
		bool first = true;

		for (const auto& i : _inputLines) {
			if (i.empty()) {
				parsed.push_back(ParsedBeaconData());
				first = true;
				continue;
			}
			auto& current = parsed.back();
			if (first) {
				const auto& scannerParts = ze::StringExtensions::splitStringByDelimeter(i, "- ");
				assert(scannerParts.size() == 2 && scannerParts[0] == "scanner");
				current.scannerNumber = std::stol(scannerParts[1]);
				first = false;
				continue;
			}

			const auto& coordParts = ze::StringExtensions::splitStringByDelimeter(i, ",");
			assert(coordParts.size() == 3);
			current.beacons.emplace_back(
				std::stol(coordParts[0]),
				std::stol(coordParts[1]),
				std::stol(coordParts[2])
			);
		}


		return parsed;
	}

	bool Day19Puzzle::areRelativelySame(BeaconDecimal _scannerNumber, BeaconDecimal _threshold, FixedBeaconData& _data, const std::vector<ze::Vector3<BeaconDecimal>>& _lhs, const std::vector<ze::Vector3<BeaconDecimal>>& _tester) {

		std::vector<std::vector<ze::Vector3<BeaconDecimal>>> rotated;
		rotated.resize(24);

		// _lhs = scanner, _rhs = point
		std::vector<std::function<ze::Vector3<BeaconDecimal>(ze::Vector3<BeaconDecimal>, ze::Vector3<BeaconDecimal>)>> translatePoints;

		for (const auto& c : _lhs) {
			// +ve x
			rotated[0].emplace_back(+c.x, +c.y, +c.z); translatePoints.emplace_back([](auto _scanner, auto _point) -> ze::Vector3<BeaconDecimal> { return { _scanner.x + _point.x, _scanner.y + _point.y, _scanner.z + _point.z }; });
			rotated[1].emplace_back(+c.x, -c.z, +c.y); translatePoints.emplace_back([](auto _scanner, auto _point) -> ze::Vector3<BeaconDecimal> { return { _scanner.x + _point.x, _scanner.y - _point.z, _scanner.z + _point.y }; });
			rotated[2].emplace_back(+c.x, -c.y, -c.z); translatePoints.emplace_back([](auto _scanner, auto _point) -> ze::Vector3<BeaconDecimal> { return { _scanner.x + _point.x, _scanner.y - _point.y, _scanner.z - _point.z }; });
			rotated[3].emplace_back(+c.x, +c.z, -c.y); translatePoints.emplace_back([](auto _scanner, auto _point) -> ze::Vector3<BeaconDecimal> { return { _scanner.x + _point.x, _scanner.y + _point.z, _scanner.z - _point.y }; });
			// -ve x
			rotated[4].emplace_back(-c.x, -c.y, +c.z); translatePoints.emplace_back([](auto _scanner, auto _point) -> ze::Vector3<BeaconDecimal> { return { _scanner.x - _point.x, _scanner.y - _point.y, _scanner.z + _point.z }; });
			rotated[5].emplace_back(-c.x, +c.z, +c.y); translatePoints.emplace_back([](auto _scanner, auto _point) -> ze::Vector3<BeaconDecimal> { return { _scanner.x - _point.x, _scanner.y + _point.z, _scanner.z + _point.y }; });
			rotated[6].emplace_back(-c.x, +c.y, -c.z); translatePoints.emplace_back([](auto _scanner, auto _point) -> ze::Vector3<BeaconDecimal> { return { _scanner.x - _point.x, _scanner.y + _point.y, _scanner.z - _point.z }; });
			rotated[7].emplace_back(-c.x, -c.z, -c.y); translatePoints.emplace_back([](auto _scanner, auto _point) -> ze::Vector3<BeaconDecimal> { return { _scanner.x - _point.x, _scanner.y - _point.z, _scanner.z - _point.y }; });
			// +ve y
			rotated[8].emplace_back(+c.y, +c.z, +c.x); translatePoints.emplace_back([](auto _scanner, auto _point) -> ze::Vector3<BeaconDecimal> { return { _scanner.x + _point.y, _scanner.y + _point.z, _scanner.z + _point.x }; });
			rotated[9].emplace_back(+c.y, -c.x, +c.z); translatePoints.emplace_back([](auto _scanner, auto _point) -> ze::Vector3<BeaconDecimal> { return { _scanner.x + _point.y, _scanner.y - _point.x, _scanner.z + _point.z }; });
			rotated[10].emplace_back(+c.y, -c.z, -c.x); translatePoints.emplace_back([](auto _scanner, auto _point) -> ze::Vector3<BeaconDecimal> { return { _scanner.x + _point.y, _scanner.y - _point.z, _scanner.z - _point.x }; });
			rotated[11].emplace_back(+c.y, +c.x, -c.z); translatePoints.emplace_back([](auto _scanner, auto _point) -> ze::Vector3<BeaconDecimal> { return { _scanner.x + _point.y, _scanner.y + _point.x, _scanner.z - _point.z }; });
			// -ve y
			rotated[12].emplace_back(-c.y, -c.z, +c.x); translatePoints.emplace_back([](auto _scanner, auto _point) -> ze::Vector3<BeaconDecimal> { return { _scanner.x - _point.y, _scanner.y - _point.z, _scanner.z + _point.x }; });
			rotated[13].emplace_back(-c.y, +c.x, +c.z); translatePoints.emplace_back([](auto _scanner, auto _point) -> ze::Vector3<BeaconDecimal> { return { _scanner.x - _point.y, _scanner.y + _point.x, _scanner.z + _point.z }; });
			rotated[14].emplace_back(-c.y, +c.z, -c.x); translatePoints.emplace_back([](auto _scanner, auto _point) -> ze::Vector3<BeaconDecimal> { return { _scanner.x - _point.y, _scanner.y + _point.z, _scanner.z - _point.x }; });
			rotated[15].emplace_back(-c.y, -c.x, -c.z); translatePoints.emplace_back([](auto _scanner, auto _point) -> ze::Vector3<BeaconDecimal> { return { _scanner.x - _point.y, _scanner.y - _point.x, _scanner.z - _point.z }; });
			// +ve z								    
			rotated[16].emplace_back(+c.z, +c.x, +c.y); translatePoints.emplace_back([](auto _scanner, auto _point) -> ze::Vector3<BeaconDecimal> { return { _scanner.x + _point.z, _scanner.y + _point.x, _scanner.z + _point.y }; });
			rotated[17].emplace_back(+c.z, -c.y, +c.x); translatePoints.emplace_back([](auto _scanner, auto _point) -> ze::Vector3<BeaconDecimal> { return { _scanner.x + _point.z, _scanner.y - _point.y, _scanner.z + _point.x }; });
			rotated[18].emplace_back(+c.z, -c.x, -c.y); translatePoints.emplace_back([](auto _scanner, auto _point) -> ze::Vector3<BeaconDecimal> { return { _scanner.x + _point.z, _scanner.y - _point.x, _scanner.z - _point.y }; });
			rotated[19].emplace_back(+c.z, +c.y, -c.x); translatePoints.emplace_back([](auto _scanner, auto _point) -> ze::Vector3<BeaconDecimal> { return { _scanner.x + _point.z, _scanner.y + _point.y, _scanner.z - _point.x }; });
			// -ve z								    
			rotated[20].emplace_back(-c.z, -c.x, +c.y); translatePoints.emplace_back([](auto _scanner, auto _point) -> ze::Vector3<BeaconDecimal> { return { _scanner.x - _point.z, _scanner.y - _point.x, _scanner.z + _point.y }; });
			rotated[21].emplace_back(-c.z, +c.y, +c.x); translatePoints.emplace_back([](auto _scanner, auto _point) -> ze::Vector3<BeaconDecimal> { return { _scanner.x - _point.z, _scanner.y + _point.y, _scanner.z + _point.x }; });
			rotated[22].emplace_back(-c.z, +c.x, -c.y); translatePoints.emplace_back([](auto _scanner, auto _point) -> ze::Vector3<BeaconDecimal> { return { _scanner.x - _point.z, _scanner.y + _point.x, _scanner.z - _point.y }; });
			rotated[23].emplace_back(-c.z, -c.y, -c.x); translatePoints.emplace_back([](auto _scanner, auto _point) -> ze::Vector3<BeaconDecimal> { return { _scanner.x - _point.z, _scanner.y - _point.y, _scanner.z - _point.x }; });
		}
		std::cout << "======================================" << std::endl;
		int rIndex = 0;
		for (const auto& r : rotated) {
			int actualMatch = 0;
			std::size_t index = 0;
			std::unordered_set<ze::Vector3<BeaconDecimal>, vector3_hash_fxn<BeaconDecimal>> scannerPositions;
			std::unordered_set<ze::Vector3<BeaconDecimal>, vector3_hash_fxn<BeaconDecimal>> beaconPositions;

			for (const auto& beacon : r) {
				for (const auto& beacon0 : _tester) {
					const auto matchingBeacon0 = beacon0;
					const auto matchingBeaconN = beacon;
					int matched = 0;
					for (const auto& n : r) {
						if (matchingBeaconN == n) { continue; }
						const auto matchedN = matchingBeaconN - n;
						for (const auto& z : _tester) {
							if (matchingBeacon0 == z) { continue; }
							const auto matchedZ = matchingBeacon0 - z;
							if (matchedN == matchedZ) {
								matched++;
							}
						}
					}
					const auto scannerNperspective = _lhs[index];
					beaconPositions.insert(scannerNperspective);
					if (matched == 11) {
						actualMatch++;
						const auto scannerPos = matchingBeacon0 - matchingBeaconN;
						scannerPositions.insert(scannerPos);
					}
				}
				index++;
			}
			if (_threshold <= actualMatch) {
				assert(scannerPositions.size() == 1);
				const auto scannerPos = *scannerPositions.begin();
				std::cout << "== Scanner pos: " << scannerPos.x << "," << scannerPos.y << "," << scannerPos.z << std::endl;

				_data.scanners[_scannerNumber] = scannerPos;
				const auto bad = _data.beacons.size() + beaconPositions.size();
				for (const auto& b : beaconPositions) {
					const auto newb = translatePoints[rIndex](scannerPos, b);
					_data.beacons.insert(newb);
					_data.beaconsFixedPerScanner[_scannerNumber].push_back(newb);
				}
				assert(_data.beacons.size() != bad);
				return true;
			}
			rIndex++;
		}

		return false;
	}
}
