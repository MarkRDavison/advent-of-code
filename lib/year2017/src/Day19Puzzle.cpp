#include <2017/Day19Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Vector2.hpp>
#include <Core/Region.hpp>

namespace TwentySeventeen {
	
	Day19Puzzle::Day19Puzzle() :
		core::PuzzleBase("A Series of Tubes", 2017, 19) {

	}
	Day19Puzzle::~Day19Puzzle() {

	}


	void Day19Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day19Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day19Puzzle::fastSolve() {

		core::Region<char> map;
		
		Vector2i startCoords;

		for (std::size_t y = 0; y < m_InputLines.size(); ++y) {
			for (std::size_t x = 0; x < m_InputLines[y].size(); ++x) {
				if (y == 0 && m_InputLines[y][x] == '|') {
					startCoords.x = (int)x;
				}
				map.getCell((int)x, (int)y) = m_InputLines[y][x];
			}
		}

		Vector2i curr = startCoords;
		Vector2i prev = { curr.x, curr.y - 1};
		map.getCell(prev.x, prev.y) = '|';

		std::string part1;
		std::size_t part2 = 0;

		while (true) {
			const auto& p = map.getCell(prev.x, prev.y);
			const auto& c = map.getCell(curr.x, curr.y);

			Vector2i next = curr;
			if (c == '+') {
				Vector2i l{ curr.x - 1, curr.y };
				Vector2i r{ curr.x + 1, curr.y };
				Vector2i u{ curr.x, curr.y - 1 };
				Vector2i d{ curr.x, curr.y + 1 };

				if (l != prev) {
					const auto nc = map.getCell(l.x, l.y);
					if (nc == '|' || nc == '-' || ('A' <= nc && nc <= 'Z')) {
						next = l;
					}
				}
				if (r != prev) {
					const auto nc = map.getCell(r.x, r.y);
					if (nc == '|' || nc == '-' || ('A' <= nc && nc <= 'Z')) {
						next = r;
					}
				}
				if (u != prev) {
					const auto nc = map.getCell(u.x, u.y);
					if (nc == '|' || nc == '-' || ('A' <= nc && nc <= 'Z')) {
						next = u;
					}
				}
				if (d!= prev) {
					const auto nc = map.getCell(d.x, d.y);
					if (nc == '|' || nc == '-' || ('A' <= nc && nc <= 'Z')) {
						next = d;
					}
				}
			}
			else if (c == '|' || c == '-') {
				next += curr - prev;
			}
			else if ('A' <= c && c <= 'Z') {
				next += curr - prev;
				part1 += c;
			}
			else if (c == ' ') {
				break;
			}

			part2++;
			prev = curr;
			curr = next;
		}


		return { part1, std::to_string(part2) };
	}
}
