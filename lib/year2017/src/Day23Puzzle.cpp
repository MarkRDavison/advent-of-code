#include <2017/Day23Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <2017/Tablet.hpp>

#define MUL 'M'

namespace TwentySeventeen {
	
	template<typename TNum>
	bool isPrime(TNum n)
	{
		if (n <= 1) {
			return false;
		}

		for (TNum i = 2; i < n; i++) {
			if (n % i == 0) {
				return false;
			}
		}

		return true;
	}

	Day23Puzzle::Day23Puzzle() :
		core::PuzzleBase("Coprocessor Conflagration", 2017, 23) {

	}
	Day23Puzzle::~Day23Puzzle() {

	}


	void Day23Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day23Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day23Puzzle::fastSolve() {

		Tablet tablet(m_InputLines);

		std::queue<TabletIntegerType> sounds0;
		std::queue<TabletIntegerType> sounds1;

		std::string part1;
		TabletIntegerType part2 = 0;

		tablet.run(sounds0, sounds1);

		part1 = std::to_string(tablet.registers[MUL]);

		TabletIntegerType b = (TabletIntegerType)std::stoull(tablet.instructions[0].arg2);
		TabletIntegerType c = b;

		b = b * (TabletIntegerType)std::stoull(tablet.instructions[4].arg2) - (TabletIntegerType)std::stoull(tablet.instructions[5].arg2);
		c = b - (TabletIntegerType)std::stoull(tablet.instructions[7].arg2);

		const auto inc = -(TabletIntegerType)std::stoull(tablet.instructions[30].arg2);

		for (TabletIntegerType i = b; i <= c; i += inc) {
			if (!isPrime(i)) {
				part2++;
			}
		}

		return { part1, std::to_string(part2) };
	}
}