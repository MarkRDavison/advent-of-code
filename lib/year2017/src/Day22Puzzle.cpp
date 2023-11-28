#include <2017/Day22Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <Core/Vector2.hpp>
#include <Core/Orientation.hpp>

namespace TwentySeventeen {
	
	Day22Puzzle::Day22Puzzle() :
		core::PuzzleBase("Sporifica Virus", 2017, 22) {

	}
	Day22Puzzle::~Day22Puzzle() {

	}


	void Day22Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day22Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	void printMap(core::Region<char>& _map, const Vector2i& _pos, core::Orientation _dir, std::size_t _iter) {
		std::cout << "========== iter " << _iter << " ==========" << std::endl;
		std::cout << "At " << _pos << " facing " << core::OrientationHelper::toString(_dir) << std::endl;

		int minY = std::min(_map.minY, _pos.y);
		int maxY = std::max(_map.maxY, _pos.y);
		int minX = std::min(_map.minX, _pos.x);
		int maxX = std::max(_map.maxX, _pos.x);

		for (int y = minY; y <= maxY; ++y) {
			for (int x = minX; x <= maxX; ++x) {
				char c = _map.getCell(x, y);
				if (c == 0) {
					c = '.';
				}
				if (x == _pos.x && y == _pos.y) {
					std::cout << "[" << c;
				}
				else if (x + 1 == _pos.x && y == _pos.y) {
					std::cout << " " << c;
				}
				else if (x - 1 == _pos.x && y == _pos.y) {
					std::cout << "]" << c;
				}
				else {
					std::cout << " " << c;
				}
			}
			std::cout << std::endl;
		}
	}

	std::pair<std::string, std::string> Day22Puzzle::fastSolve() {
		return fastSolve(10000, 10000000);
	}

	std::pair<std::string, std::string> Day22Puzzle::fastSolve(std::size_t _iter1, std::size_t _iter2) {

		int yHalfSize = (int)(m_InputLines.size() / 2);
		int xHalfSize = (int)(m_InputLines[0].size() / 2);

		std::size_t part1 = 0;
		std::size_t part2 = 0;

		if (getVerbose()) {
			std::cout << "Part 1" << std::endl;
		}
		 {
			core::Region<char> map;

			Vector2i pos{ 0, 0 };
			core::Orientation dir = core::Orientation::Up;
			{
				std::size_t yy = 0;
				for (int y = -yHalfSize; y <= +yHalfSize; ++y) {
					std::size_t xx = 0;
					for (int x = -xHalfSize; x <= +xHalfSize; ++x) {
						map.getCell(x, y) = m_InputLines[yy][xx];
						xx++;
					}
					yy++;
				}
			}

			if (getVerbose()) {
				printMap(map, pos, dir, 0);
			}

			for (std::size_t i = 0; i < _iter1; ++i) {

				auto& current = map.getCell(pos.x, pos.y);

				if (current == '#') {
					dir = core::OrientationHelper::turn(dir, core::Orientation::Right);
					current = '.';
				}
				else {
					dir = core::OrientationHelper::turn(dir, core::Orientation::Left);
					current = '#';
					part1++;
				}


				pos.x += core::OrientationHelper::toDirection(dir).x;
				pos.y -= core::OrientationHelper::toDirection(dir).y;

				if (getVerbose()) {
					printMap(map, pos, dir, i + 1);
				}
			}
		}
		if (getVerbose()) {
			std::cout << "Part 2" << std::endl;
		}
		{
			core::Region<char> map;

			Vector2i pos{ 0, 0 };
			core::Orientation dir = core::Orientation::Up;
			{
				std::size_t yy = 0;
				for (int y = -yHalfSize; y <= +yHalfSize; ++y) {
					std::size_t xx = 0;
					for (int x = -xHalfSize; x <= +xHalfSize; ++x) {
						map.getCell(x, y) = m_InputLines[yy][xx];
						xx++;
					}
					yy++;
				}
			}

			if (getVerbose()) {
				printMap(map, pos, dir, 0);
			}

			for (std::size_t i = 0; i < _iter2; ++i) {
				auto& current = map.getCell(pos.x, pos.y);

				if (current == '.' || current == 0) {
					dir = core::OrientationHelper::turn(dir, core::Orientation::Left);
					current = 'W';
				}
				else if (current == '#') {
					dir = core::OrientationHelper::turn(dir, core::Orientation::Right);
					current = 'F';
				}
				else if (current == 'F') {
					dir = core::OrientationHelper::reverse(dir);
					current = '.';
				}
				else if (current == 'W') {
					// no turn
					current = '#';
					part2++;
				}

				pos.x += core::OrientationHelper::toDirection(dir).x;
				pos.y -= core::OrientationHelper::toDirection(dir).y;

				if (getVerbose()) {
					printMap(map, pos, dir, i + 1);
				}
			}
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
