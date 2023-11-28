#include <2016/Day23Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <2016/AssembunyMachine.hpp>

namespace TwentySixteen {
	
	Day23Puzzle::Day23Puzzle() :
		core::PuzzleBase("Safe Cracking", 2016, 23) {

	}
	Day23Puzzle::~Day23Puzzle() {

	}


	void Day23Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day23Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day23Puzzle::fastSolve() {
		AssembunnyInteger part1;
		AssembunnyInteger part2;
		{
			AssembunyMachine machine = AssembunyMachine(m_InputLines);

			machine.registers[0] = 7;

			while (machine.programCounter >= 0 && machine.programCounter < m_InputLines.size()) {
				machine.applyInstructionAtPC();
			}
			part1 = machine.registers[0];
		}
		{
			AssembunyMachine machine = AssembunyMachine(m_InputLines);

			machine.registers[0] = 12;

			

			while (machine.programCounter >= 0 && machine.programCounter < m_InputLines.size()) {
				machine.applyInstructionAtPC();

				if (machine.registers[3] % 1000000 == 0) {
					std::cout << machine.registers[0] << " - " << machine.registers[1] << " - " << machine.registers[2] << " - " << machine.registers[3] << std::endl;
				}
			}
			part2 = machine.registers[0];
		}
		return { std::to_string(part1), std::to_string(part2) };
	}
}
