#include <2017/Day10Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <algorithm>
#include <numeric>
#include <sstream>
#include <array>

namespace TwentySeventeen {
	
	Day10Puzzle::Day10Puzzle() :
		core::PuzzleBase("Knot Hash", 2017, 10) {

	}
	Day10Puzzle::~Day10Puzzle() {

	}


	void Day10Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day10Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day10Puzzle::fastSolve() {
		return { fastSolve(256, false, {}), fastSolve(256, true, { 17, 31, 73, 47, 23 }) };
	}

	std::string Day10Puzzle::fastSolve(std::size_t _maxSize, bool _ascii, const std::vector<HashNumber>& _additional) {
		std::vector<int> data(_maxSize);
		std::iota(std::begin(data), std::end(data), 0);


		std::vector<HashNumber> input;

		if (_ascii) {
			for (const auto c : m_InputLines[0]) {
				input.push_back((HashNumber)c);
			}
		}
		else {
			for (const auto& p : ze::StringExtensions::splitStringByDelimeter(m_InputLines[0], " ,")) {
				input.push_back((HashNumber)std::stoul(p));
			}
		}

		for (const auto& add : _additional) {
			input.push_back(add);
		}

		HashNumber curr = 0;
		HashNumber skip = 0;
		HashNumber iter = _ascii ? 64 : 1;
		for (std::size_t i = 0; i < iter; ++i) {
			for (const auto& n : input) {
				const auto nToUse = n;
				for (std::size_t j = 0; j < nToUse / 2; ++j) {
					std::size_t lhi = (curr + j) % _maxSize;
					std::size_t rhi = (curr + nToUse - j - 1) % _maxSize;

					std::swap(data[lhi], data[rhi]);
				}

				curr += nToUse + skip;
				curr %= _maxSize;

				skip++;
			}
		}

		if (_ascii) {
			std::string answer;
			for (std::size_t di = 0; di < 16; di++)
			{
				const auto hashVal =
					data[di * 16 +  0] ^
					data[di * 16 +  1] ^
					data[di * 16 +  2] ^
					data[di * 16 +  3] ^
					data[di * 16 +  4] ^
					data[di * 16 +  5] ^
					data[di * 16 +  6] ^
					data[di * 16 +  7] ^
					data[di * 16 +  8] ^
					data[di * 16 +  9] ^
					data[di * 16 + 10] ^
					data[di * 16 + 11] ^
					data[di * 16 + 12] ^
					data[di * 16 + 13] ^
					data[di * 16 + 14] ^
					data[di * 16 + 15];

				std::stringstream stream;
				stream << std::hex << hashVal;

				std::string part = stream.str();
				if (part.size() == 1) {
					part = "0" + part;
				}
				answer += part;
			}

			return answer;
		}
		else {
			return std::to_string(data[0] * data[1]);
		}
	}

	
	std::string Day10Puzzle::knotHash(const std::string& _input) {
		auto puzzle = Day10Puzzle();
		puzzle.setInputLines({ _input });
		return puzzle.fastSolve(256, true, { 17, 31, 73, 47, 23 });
	}
}
