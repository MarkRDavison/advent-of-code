#include <2016/Day20Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentySixteen {
	
	Day20Puzzle::Day20Puzzle() :
		core::PuzzleBase("Firewall Rules", 2016, 20) {

	}
	Day20Puzzle::~Day20Puzzle() {

	}


	void Day20Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day20Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day20Puzzle::fastSolve() {
		return fastSolve(4294967295);
	}

	std::pair<std::string, std::string> Day20Puzzle::fastSolve(IpValue _max) {
		std::vector<std::pair<IpValue, IpValue>> ranges;
		for (const auto& line : m_InputLines) {
			const auto& parts = StringExtensions::splitStringByDelimeter(line, "-");
			ranges.emplace_back((IpValue)std::stoull(parts[0]), (IpValue)std::stoull(parts[1]));
		}

		bool* data = new bool[_max];
		for (IpValue i = 0; i < _max; ++i) {
			data[i] = true;
		}

		for (const auto& [start, end] : ranges) {
			for (IpValue i = start; i <= end && i < _max; ++i) {
				data[i] = false;
			}
		}

		IpValue part1 = 0;
		IpValue part2 = 0;
		for (IpValue i = 0; i < _max; ++i) {
			if (data[i]) {
				part2++;
				if (part1 == 0) {
					part1 = i;
				}
			}
		}

		delete[] data;

		return { std::to_string(part1), std::to_string(part2) };
	}
}
