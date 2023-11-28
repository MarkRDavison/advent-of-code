#include <2021/Day20Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Vector2.hpp>
#include <cassert>
#include <array>

namespace TwentyTwentyOne {

	void print(const std::vector<std::vector<int>>& _set) {
		std::cout << "==================================" << std::endl;
		for (int y = 0; y < _set.size(); ++y) {
			for (int x = 0; x < _set[y].size(); ++x) {
				const bool set = _set[y][x];
				std::cout << (set ? '#' : '.');
			}
			std::cout << std::endl;
		}
	}
	
	Day20Puzzle::Day20Puzzle() :
		core::PuzzleBase("Trench Map", 2021, 20) {
	}


	void Day20Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByLines(StringExtensions::loadFileToString(_initialisationInfo.parameters[0])));
	}

	void Day20Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	template <int NUM_STEPS>
	bool inBounds(const int _step, const int _y, const int _x, const std::vector<std::vector<int>>& _image) {
		return _y >= (NUM_STEPS - _step) && _x >= (NUM_STEPS - _step) && _y < _image.size() - (NUM_STEPS - _step) && _x < _image[0].size() - (NUM_STEPS - _step);
	};

	template <int NUM_STEPS>
	std::string getBinaryString(const int _step, const int _y, const int _x, const std::vector<int>& _algorithm, const std::vector<std::vector<int>>& _image) {
		std::string str;

		for (int x = -1; x <= 1; ++x) {
			for (int y = -1; y <= 1; ++y) {
				if (inBounds<NUM_STEPS>(_step, _y + x, _x + y, _image)) {
					str += _image[_y + x][_x + y] + '0';
				} else if (_algorithm[0] == 0) {
					str += '0';
				} else if (_step % 2 == 0) {
					str += _algorithm[511] + '0';;
				} else {
					str += _algorithm[0] + '0';;
				}
			}
		}

		return str;
	};

	template <int NUM_STEPS>
	int solve(const std::vector<int>& _algorithm, const std::vector<std::vector<int>>& _inputImage) {

		const auto startHeight = _inputImage.size();
		const auto startWidth = _inputImage[0].size();
		const auto totalHeight = 2 * 2 * (NUM_STEPS)+startHeight;
		const auto totalWidth = 2 * 2 * (NUM_STEPS)+startWidth;

		std::vector<std::vector<std::vector<int>>> images(
			NUM_STEPS + 1,
			std::vector<std::vector<int>>(
				totalHeight,
				std::vector<int>(
					totalWidth, 0)));

		{
			auto& first = images[0];
			for (int y = 0; y < startHeight; y++) {
				for (int x = 0; x < startWidth; x++) {
					first[2 * NUM_STEPS + y][2 * NUM_STEPS + x] = _inputImage[y][x];
				}
			}
		}


		for (int step = 0; step < NUM_STEPS; step++) {
			auto& img = images[step + 1];
			for (int y = 0; y < totalHeight; y++) {
				for (int x = 0; x < totalWidth; x++) {
					const auto binaryString = getBinaryString<NUM_STEPS>(step, y, x, _algorithm, images[step]);
					img[y][x] = _algorithm[std::stoi(binaryString, nullptr, 2)];
				}
			}
		}

		int count = 0;
		{
			auto& finalImage = images[NUM_STEPS];
			for (int y = 1; y < totalHeight - 1; y++) {
				for (int x = 1; x < totalWidth - 1; x++) {
					count += finalImage[y][x];
				}
			}
		}

		return count;
	}

	std::pair<std::string, std::string> Day20Puzzle::fastSolve() {
		const auto& [algorithm, inputImage] = parse(m_InputLines);

		const auto part1 = solve<2>(algorithm, inputImage);
		const auto part2 = solve<50>(algorithm, inputImage);

		return { std::to_string(part1), std::to_string(part2) };
	}

	std::pair<std::vector<int>, std::vector<std::vector<int>>> Day20Puzzle::parse(const std::vector<std::string>& _inputLines) {
		std::vector<std::vector<int>> on;
		std::vector<int> alg;
		constexpr int yOff = 2;
		for (int y = 0; y < _inputLines.size() - 2; ++y) {
			auto& row = on.emplace_back();
			for (int x = 0; x < _inputLines[y + yOff].size(); ++x) {
				const char c = _inputLines[y + yOff][x];
				row.push_back(c == '#' ? 1 : 0);
			}
		}

		for (const auto& c : _inputLines[0]) {
			alg.push_back(c == '#' ? 1 : 0);
		}

		return { alg, on };
	}

}
