#include <2021/Day13Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <cassert>

namespace TwentyTwentyOne {

	void dumpRegion(const core::Region<bool>& _region) {
		std::cout << "=======================================" << std::endl;
		for (int y = _region.minY; y <= _region.maxY; ++y) {
			for (int x = _region.minX; x <= _region.maxX; ++x) {
				std::cout << (_region.getCell(x, y) ? "@" : " ");
			}
			std::cout << std::endl;
		}
		std::cout << "=======================================" << std::endl;
	}
	
	Day13Puzzle::Day13Puzzle() :
		core::PuzzleBase("Transparent Origami", 2021, 13) {
	}

	void Day13Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByLines(StringExtensions::loadFileToString(_initialisationInfo.parameters[0])));
	}

	void Day13Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {		
		m_InputLines = std::vector<std::string>(_inputLines);
	}
	
	void fold(core::Region<bool>& _region, const Fold& _fold) {
		if (_fold.horizontal) {
			const auto foldY = _fold.index;

			for (int y = foldY + 1; y <= _region.maxY; ++y) {
				for (int x = _region.minX; x <= _region.maxX; ++x) {
					auto& belowFold = _region.getCell(x, y);
					auto& aboveFold = _region.getCell(x, y - 2 * (y - foldY));
					if (belowFold) {
						aboveFold = true;
						belowFold = false;
					}
				}
			}

			_region.maxY = foldY - 1;
		}
		else {
			const auto foldX = _fold.index;

			for (int y = _region.minY; y <= _region.maxY; ++y) {
				for (int x = foldX + 1; x <= _region.maxX; ++x) {
					auto& rightFold = _region.getCell(x, y);
					auto& LeftFold = _region.getCell(x - 2 * (x - foldX), y);
					if (rightFold) {
						LeftFold = true;
						rightFold = false;
					}
				}
			}

			_region.maxX = foldX - 1;
		}
	}

	int countDots(const core::Region<bool>& _region) {
		int count = 0;

		for (int y = _region.minY; y <= _region.maxY; ++y) {
			for (int x = _region.minX; x <= _region.maxX; ++x) {
				if (_region.getCell(x, y)) {
					count++;
				}
			}
		}

		return count;
	}

	std::pair<std::string, std::string> Day13Puzzle::fastSolve() {
		auto [region, instructions] = parse(m_InputLines);

		fold(region, instructions[0]);
		const auto part1 = countDots(region);

		for (unsigned i = 1; i < instructions.size(); ++i) {
			fold(region, instructions[i]);
		}

		dumpRegion(region);

		return { std::to_string(part1), "See above" };
	}

	std::pair<core::Region<bool>, std::vector<Fold>> Day13Puzzle::parse(const std::vector<std::string>& _inputLines) {
		core::Region<bool> region;
		std::vector<Fold> instructions;

		unsigned i;
		for (i = 0; i < _inputLines.size(); ++i) {
			const auto& str = _inputLines[i];
			if (str.empty()) {
				i++;
				break;
			}
			const auto& coords = StringExtensions::splitStringByDelimeter(str, ",");
			assert(coords.size() == 2);

			auto& cell = region.getCell(std::stoi(coords[0]), std::stoi(coords[1]));
			cell = true;
		}
		for (; i < _inputLines.size(); ++i) {
			const auto& foldparts = StringExtensions::splitStringByDelimeter(_inputLines[i], " =");
			assert(foldparts.size() == 4);

			auto& instr = instructions.emplace_back();
			instr.horizontal = foldparts[2] == "y";
			instr.index = std::stoi(foldparts[3]);
		}

		return { region, instructions };
	}
}
