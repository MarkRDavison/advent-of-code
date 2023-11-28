#include <2017/Day11Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentySeventeen {


	void Hex::operator+=(const Hex& _b) {
		q = q + _b.q;
		r = r + _b.r;
		s = -q - r;
	}
	Hex& Hex::operator=(const Hex& _b) {
		q = _b.q;
		r = _b.r;
		s = _b.s;
		return *this;
	}

	int Hex::length() const {
		return (std::abs(q) + std::abs(r) + std::abs(s)) / 2;
	}

	Day11Puzzle::Day11Puzzle() :
		core::PuzzleBase("Hex Ed", 2017, 11) {

	}
	Day11Puzzle::~Day11Puzzle() {

	}


	void Day11Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day11Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day11Puzzle::fastSolve() {
		const auto& [part1, part2] = apply(m_InputLines[0]);

		return {
			std::to_string(part1.length()),
			std::to_string(part2)
		};
	}

	std::pair<Hex, int> Day11Puzzle::apply(const std::string& _input) {
		Hex loc(0, 0);
		int max = 0;

		for (const auto& dir : StringExtensions::splitStringByDelimeter(_input, ",")) {
			if (dir == "n") {
				loc += Hex(+0, -1);
			}
			else if (dir == "ne") {
				loc += Hex(+1, -1);
			}
			else if (dir == "nw") {
				loc += Hex(-1, +0);
			}
			else if (dir == "s") {
				loc += Hex(+0, +1);
			}
			else if (dir == "se") {
				loc += Hex(+1, +0);
			}
			else if (dir == "sw") {
				loc += Hex(-1, +1);
			}

			max = std::max(max, loc.length());
		}

		return { loc, max };
	}
}
