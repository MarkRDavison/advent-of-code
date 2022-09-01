#include <2017/Day14Puzzle.hpp>
#include <2017/Day10Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <unordered_set>

namespace TwentySeventeen {
	
	Day14Puzzle::Day14Puzzle() :
		core::PuzzleBase("Disk Defragmentation", 2017, 14) {

	}
	Day14Puzzle::~Day14Puzzle() {

	}


	void Day14Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day14Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	const char* hex_char_to_bin(char c)
	{
		switch (toupper(c))
		{
			case '0': return "0000";
			case '1': return "0001";
			case '2': return "0010";
			case '3': return "0011";
			case '4': return "0100";
			case '5': return "0101";
			case '6': return "0110";
			case '7': return "0111";
			case '8': return "1000";
			case '9': return "1001";
			case 'A': return "1010";
			case 'B': return "1011";
			case 'C': return "1100";
			case 'D': return "1101";
			case 'E': return "1110";
			case 'F': return "1111";
			default:  throw std::runtime_error("Invalid hex character");
		}
	}

	static void floodRemove(core::Region<char>& _region, int _x, int _y) {

		if (_x < 0 || _y < 0 || _x >= 128 || _y >= 128) {
			return;
		}

		auto& cell = _region.getCell(_x, _y);

		if (cell != '#') {
			return;
		}

		cell = '.';
		floodRemove(_region, _x - 1, _y + 0);
		floodRemove(_region, _x + 1, _y + 0);
		floodRemove(_region, _x + 0, _y - 1);
		floodRemove(_region, _x + 0, _y + 1);
	}

	std::pair<std::string, std::string> Day14Puzzle::fastSolve() {
		core::Region<char> region;

		int part1 = 0;

		for (int y = 0; y < 128; ++y) {
			const auto& hash = Day10Puzzle::knotHash(m_InputLines[0] + "-" + std::to_string(y));

			for (int x = 0; x < 32; ++x) {
				const auto bin4 = hex_char_to_bin(hash[x]);

				region.getCell((x * 4) + 0, y) = bin4[0] == '1' ? '#' : '.';
				region.getCell((x * 4) + 1, y) = bin4[1] == '1' ? '#' : '.';
				region.getCell((x * 4) + 2, y) = bin4[2] == '1' ? '#' : '.';
				region.getCell((x * 4) + 3, y) = bin4[3] == '1' ? '#' : '.';
			}
		}

		for (int y = 0; y < 128; ++y) {
			for (int x = 0; x < 128; ++x) {
				char c = region.getCell(x, y);
				if (c == '#') {
					part1++;
				}
			}
		}

		int part2 = 0;
		

		std::unordered_set<int> seenIndex;
		for (int y = 0; y < 128; ++y) {
			for (int x = 0; x < 128; ++x) {
				const auto cell = region.getCell(x, y);
				if (cell == '#') {
					part2++;
					floodRemove(region, x, y);
				}
			}
		}
		
		return { std::to_string(part1), std::to_string(part2) };
	}
}
