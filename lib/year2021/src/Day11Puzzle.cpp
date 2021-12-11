#include <2021/Day11Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <zeno-engine/Core/Vector2.hpp>
#include <queue>

namespace TwentyTwentyOne {

	Day11Puzzle::Day11Puzzle() :
		core::PuzzleBase("Dumbo Octopus", 2021, 11) {
	}


	void Day11Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day11Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day11Puzzle::fastSolve() {
		auto region = parse(m_InputLines);
		long part1 = 0;
		for (unsigned i = 0; i < 100; ++i) {
			part1 += iterate(region);
		}
		auto region2 = parse(m_InputLines);
		long i = 0;
		while (true) {
			i++;

			const auto flashCount = iterate(region2);
			if (flashCount == 100) {				
				return { std::to_string(part1), std::to_string(i) };
			}
		}
	}

	core::Region<Octopus> Day11Puzzle::parse(const std::vector<std::string>& _inputLines) {
		core::Region<Octopus> region;

		for (int y = 0; y < 10; ++y) {
			for (int x = 0; x < 10; ++x) {
				auto& o = region.getCell(x, y);
				o.energy = _inputLines[y][x] - '0';
				o.valid = true;
			}
		}

		return region;
	}
	
	long Day11Puzzle::iterate(core::Region<Octopus>& _region) {
		long flashCount = 0;
		std::queue<ze::Vector2i> flashed;
		for (int y = 0; y < 10; ++y) {
			for (int x = 0; x < 10; ++x) {
				auto& o = _region.getCell(x, y);
				o.energy++;
				if (o.energy > 9) {
					flashed.push({ x, y });
					o.flashed = true;
					flashCount++;
				}
			}
		}

		while (!flashed.empty()) {
			const auto coord = flashed.front();
			flashed.pop();
			auto& o = _region.getCell(coord.x, coord.y);
			for (int ny = -1; ny <= +1; ++ny) {
				for (int nx = -1; nx <= +1; ++nx) {
					auto& no = _region.getCell(coord.x + nx, coord.y + ny);
					if (no.valid && !no.flashed) {
						no.energy++;
						if (no.energy > 9) {
							no.flashed = true;
							flashed.push({ coord.x + nx, coord.y + ny });
							flashCount++;
						}
					}
				}
			}
		}
		for (int y = 0; y < 10; ++y) {
			for (int x = 0; x < 10; ++x) {
				auto& o = _region.getCell(x, y);
				if (o.flashed) {
					o.flashed = false;
					o.energy = 0;
				}
			}
		}

		return flashCount;
	}


	bool Day11Puzzle::validate(core::Region<Octopus>& _region, const std::vector<std::string>& _desired) {
		for (int y = 0; y < 10; ++y) {
			for (int x = 0; x < 10; ++x) {
				auto& o = _region.getCell(x, y);
				if (o.energy != _desired[y][x] - '0') {
					return false;
				}
			}
		}

		return true;
	}
}
