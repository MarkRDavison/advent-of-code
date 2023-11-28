#include <2017/Day08Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_map>

namespace TwentySeventeen {

	using RegisterValue = long;
	using Registers = std::unordered_map<std::string, RegisterValue>;

	Day08Puzzle::Day08Puzzle() :
		core::PuzzleBase("I Heard You Like Registers", 2017, 8) {

	}
	Day08Puzzle::~Day08Puzzle() {

	}


	void Day08Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day08Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day08Puzzle::fastSolve() {
		Registers registers;

		RegisterValue part1 = 0;
		RegisterValue part2 = 0;

		for (const auto& l : m_InputLines) {
			const auto& parts = StringExtensions::splitStringByDelimeter(l, " ");
			const auto destRegisterName = parts[0];
			const auto change = ((RegisterValue)std::stol(parts[2])) * (parts[1] == "inc" ? +1 : -1);

			const auto val1 = parts[4];
			const auto val2 = parts[6];

			const auto number1 = ('a' <= val1[0] && val1[0] <= 'z') ? registers[val1] : (RegisterValue)std::stol(val1);
			const auto number2 = ('a' <= val2[0] && val2[0] <= 'z') ? registers[val2] : (RegisterValue)std::stol(val2);

			bool result = false;

			const auto op = parts[5];

			if (op == ">") {
				result = number1 > number2;
			}
			else if (op == "<") {
				result = number1 < number2;
			}
			else if (op == ">=") {
				result = number1 >= number2;
			}
			else if (op == "<=") {
				result = number1 <= number2;
			}
			else if (op == "==") {
				result = number1 == number2;
			}
			else if (op == "!=") {
				result = number1 != number2;
			}
			else {
				throw std::runtime_error("Unhandled operation");
			}

			if (result) {
				registers[destRegisterName] += change;
				part2 = std::max(registers[destRegisterName], part2);
			}
		}

		for (const auto& [name, value] : registers) {
			part1 = std::max(part1, value);
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
