#include <2020/Day20Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cassert>
#include <numeric>
#include <bitset>
#include <cmath>

namespace TwentyTwenty {

	// TODO: Move this to utility framework
	std::vector<std::string> splitStringByLines6(const std::string& _parameter) {
		std::vector<std::string> result;
		std::stringstream stringStream(_parameter);
		std::string line;
		while (std::getline(stringStream, line)) {
			result.push_back(line);
		}

		return result;
	}

	Day20Puzzle::Day20Puzzle() :
		core::PuzzleBase("Jurassic Jigsaw", 2020, 20) {
	}


	void Day20Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(splitStringByLines6(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0])));
	}

	void Day20Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day20Puzzle::fastSolve() {
		const auto& parsed = Day20Puzzle::parse(m_InputLines);

		const auto part1 = Day20Puzzle::doPart1(parsed);
		const auto part2 = Day20Puzzle::doPart2(parsed);

		return { part1, part2 };
	}

	Parsed Day20Puzzle::parse(const std::vector<std::string>& _inputLines) {
		Parsed parsed;

		for (unsigned i = 0; i < _inputLines.size(); ++i) {
			if (_inputLines[i].find("Tile ") == 0) {
				auto& current = parsed.emplace_back();
				current.id = std::stol(_inputLines[i].substr(5));
				continue;
			}
			if (_inputLines[i].empty()) {
				continue;
			}

			auto& current = parsed.back();
			current.tiles.push_back(_inputLines[i]);
		}

		for (auto& current : parsed) {
			{
				std::bitset<10> top;
				std::bitset<10> topReverse;
				for (unsigned i = 0; i < 10; ++i) {
					top[10 - 1 - i] = (current.tiles[0][i] == '#'
						? 1
						: 0);
					topReverse[i] = top[10 - 1 - i];
				}

				//current.top = top.to_ulong();
				//current.topReverse = topReverse.to_ulong();
			}
			{
				std::bitset<10> bottom;
				std::bitset<10> bottomReverse;
				for (unsigned i = 0; i < 10; ++i) {
					bottom[10 - 1 - i] = (current.tiles[9][i] == '#'
						? 1
						: 0);
					bottomReverse[i] = bottom[10 - 1 - i];
				}

				//current.bottom = bottom.to_ulong();
				//current.bottomReverse = bottomReverse.to_ulong();
			}
			{
				std::bitset<10> left;
				std::bitset<10> leftReverse;
				for (unsigned i = 0; i < 10; ++i) {
					left[10 - 1 - i] = (current.tiles[i][0] == '#'
						? 1
						: 0);
					leftReverse[i] = left[10 - 1 - i];
				}

				//current.left = left.to_ulong();
				//current.leftReverse = leftReverse.to_ulong();
			}
			{
				std::bitset<10> right;
				std::bitset<10> rightReverse;
				for (unsigned i = 0; i < 10; ++i) {
					right[10 - 1 - i] = (current.tiles[i][9] == '#'
						? 1
						: 0);
					rightReverse[i] = right[10 - 1 - i];
				}

				//current.right = right.to_ulong();
				//current.rightReverse = rightReverse.to_ulong();
			}
		}

		return parsed;
	}

	static char getAtIndex(const Parsed& _parsed, const std::vector<unsigned>& _iota, unsigned _x, unsigned _y, unsigned _size) {
		const unsigned image_x = _x / 10;
		const unsigned image_y = _y / 10;

		const unsigned image_pix_x = _x % 10;
		const unsigned image_pix_y = _y % 10;

		const auto& image = _parsed[_iota[image_y * _size + image_x]];

		return 'a';// image[(image_pix_y * 10) + (image_pix_x)];
	}

	static bool validate(const Parsed& _parsed, const std::vector<unsigned>& _iota, unsigned _size) {
		for (unsigned y = 0; y < 10 * _size; ++y) {
			for (unsigned x = 0; x < 10 * _size; ++x) {

				if ((x % 10) != 0 && (y % 10) != 0 && (x % 10) != 9 && (y % 10) != 9) {
					continue;
				}

				const unsigned image_x = x / 10;
				const unsigned image_y = y / 10;

				const unsigned image_pix_x = x % 10;
				const unsigned image_pix_y = y % 10;

				const auto& image = _parsed[_iota[image_y * _size + image_x]];

				//const char c = image[image_pix_y * 10 + image_pix_x];
			}
		}

		for (unsigned x = 0; x < 10 * _size; x += 1) {
			for (unsigned y = 9; y < 10 * _size - 1; y += 10) {

				const char top = getAtIndex(_parsed, _iota, x, y + 0, _size);
				const char bot = getAtIndex(_parsed, _iota, x, y + 1, _size);

				if (top != bot) {
					return false;
				}
			}
		}

		for (unsigned y = 0; y < 10 * _size; y += 1) {
			for (unsigned x = 9; x < 10 * _size - 1; x += 10) {

				const char left = getAtIndex(_parsed, _iota, x + 0, y, _size);
				const char right = getAtIndex(_parsed, _iota, x + 1, y, _size);

				if (left != right) {
					return false;
				}
			}
		}

		return true;
	}

	std::string Day20Puzzle::doPart1(const Parsed& _parsed) {
		assert(std::sqrt(_parsed.size()) * std::sqrt(_parsed.size()) == _parsed.size());

		const unsigned size = static_cast<unsigned>(std::sqrt(_parsed.size()));


		for (unsigned i = 0; i < _parsed.size(); ++i) {
			for (unsigned r = 0; r < 8; ++r) {
				std::vector<unsigned> l(_parsed.size());
				std::iota(l.begin(), l.end(), 0);

				Parsed p(_parsed);

				do {
					if (validate(p, l, size)) {
						std::cout << "Valid:" << std::endl;
						for (unsigned index = 0; index < _parsed.size(); index += size) {
							for (unsigned indexI = 0; indexI < size; ++indexI) {
								std::cout << _parsed[l[index + indexI]].id << '\t';
							}
						}
					}
				} while (std::next_permutation(l.begin(), l.end()));

				std::cout << i << ", " << r << " complete" << std::endl;
			}
		}
		

		return "";
	}

	std::string Day20Puzzle::doPart2(const Parsed& _parsed) {
		return "";
	}
}
