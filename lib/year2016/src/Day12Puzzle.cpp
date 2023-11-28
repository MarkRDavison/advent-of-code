#include <2016/Day12Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <cassert>
#include <2016/AssembunyMachine.hpp>

namespace TwentySixteen {
	
	Day12Puzzle::Day12Puzzle() :
		core::PuzzleBase("Leonardo's Monorail", 2016, 12) {

	}
	Day12Puzzle::~Day12Puzzle() {

	}


	void Day12Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day12Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day12Puzzle::fastSolve() {
		AssembunnyInteger part1;
		AssembunnyInteger part2;

		{
			AssembunyMachine machine = AssembunyMachine(m_InputLines);

			long prev = machine.registers[3];
			while (machine.programCounter >= 0 && machine.programCounter < (long)m_InputLines.size()) {
				machine.applyInstructionAtPC();

				if (prev != machine.registers[3]) {
					prev = machine.registers[3];
					std::cout << "PC: " << machine.programCounter
						<< " - [" << machine.registers[0]
						<< ", " << machine.registers[1]
						<< ", " << machine.registers[2]
						<< ", " << machine.registers[3]
						<< "]" << std::endl;
				}
			}

			part1 = machine.registers[0];
		}
		{
			AssembunyMachine machine(m_InputLines);
			machine.registers[2] = 1;

			long prev = machine.registers[3];

			while (machine.programCounter >= 0 && machine.programCounter < (long)m_InputLines.size()) {
				machine.applyInstructionAtPC();

				if (prev != machine.registers[3]) {
					prev = machine.registers[3];
					std::cout << "PC: " << machine.programCounter
						<< " - [" << machine.registers[0]
						<< ", " << machine.registers[1]
						<< ", " << machine.registers[2]
						<< ", " << machine.registers[3]
						<< "]" << std::endl;
				}
			}

			part2 = machine.registers[0];
		}


		return { std::to_string(part1), std::to_string(part2) };
	}

}
