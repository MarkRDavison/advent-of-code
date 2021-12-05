#include <2021/Day05Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <algorithm>
#include <cassert>

namespace TwentyTwentyOne {
		
	Day05Puzzle::Day05Puzzle() :
		core::PuzzleBase("Hydrothermal Venture", 2021, 5) {
	}


	void Day05Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day05Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day05Puzzle::fastSolve() {
		const auto& part1Parsed = parseInput(m_InputLines, true);
		const auto& part2Parsed = parseInput(m_InputLines, false);
		const auto part1 = solveOverlaps(part1Parsed);
		const auto part2 = solveOverlaps(part2Parsed);
		return { part1, part2 };
	}
	VecPoints Day05Puzzle::parseInput(const std::vector<std::string>& _inputLines, bool _straightOnly) {
		VecPoints parsed;

		for (const auto& i : _inputLines) {
			const auto& s = ze::StringExtensions::splitStringByDelimeter(i, ", ->");

			assert(s.size() == 4);

			const auto p1 = ze::Vector2i(std::stoi(s[0]), std::stoi(s[1]));
			const auto p2 = ze::Vector2i(std::stoi(s[2]), std::stoi(s[3]));

			if (_straightOnly) {
				if (p1.x != p2.x && p1.y != p2.y) {
					continue;
				}
			}

			parsed.emplace_back(p1, p2);
		}

		return parsed;
	}

	std::string Day05Puzzle::solveOverlaps(const VecPoints& _points) {

		core::Region<int> region;

		for (const auto& [p1t, p2t] : _points) {
			ze::Vector2i p1(p1t);
			ze::Vector2i p2(p2t);

			if (p1.x != p2.x && p1.y != p2.y) {

				if (p1.x > p2.x) {
					p1 = p2t;
					p2 = p1t;
				}

				ze::Vector2i dir;

				if (p1.y > p2.y) {
					dir = { 1, -1 };
				}
				else {
					dir = { 1, +1 };
				}

				for (int i = 0; i < 1 + p2.x - p1.x; ++i) {
					const auto newPoint = p1 + dir * i;
					auto& cell = region.getCell(newPoint.x, newPoint.y);
					cell += 1;
				}
			}
			else {
				if (p1t.x > p2t.x) {
					p1 = p2t;
					p2 = p1t;
				} else if (p1t.y > p2t.y) {
					p1 = p2t;
					p2 = p1t;
				}

				for (int y = p1.y; y <= p2.y; ++y) {
					for (int x = p1.x; x <= p2.x; ++x) {
						auto& cell = region.getCell(x, y);
						cell += 1;
					}
				}
			}
			
		}

		int count = 0;

		for (int y = region.minY; y <= region.maxY; ++y) {
			for (int x = region.minX; x <= region.maxX; ++x) {
				const auto val = region.getCell(x, y);
				if (val > 1) {
					count++;
				}
			}
		}

		return std::to_string(count);
	}
}
