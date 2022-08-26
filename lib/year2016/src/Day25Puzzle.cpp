#include <2016/Day25Puzzle.hpp>
#include <2016/AssembunyMachine.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <iostream>

namespace TwentySixteen {
	
	Day25Puzzle::Day25Puzzle() :
		core::PuzzleBase("Clock Signal", 2016, 25) {

	}
	Day25Puzzle::~Day25Puzzle() {

	}


	void Day25Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day25Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day25Puzzle::fastSolve() {

		int maxIters = 0;
		for (AssembunnyInteger i = 0;; ++i) {
			AssembunyMachine machine = AssembunyMachine(m_InputLines);
			machine.registers[0] = i;
			int currentIters = 0;
			AssembunnyInteger expected = 0;
			if (i > 50000) {
				throw std::runtime_error("Something went wrong, should have resolved by now");
			}
			while (machine.programCounter >= 0 && machine.programCounter < m_InputLines.size()) {
				currentIters++;
				machine.applyInstructionAtPC();
				if (!machine.output.empty()) {
					auto output = machine.output.front();
					if (output == expected) {
						expected = (output == 0 ? 1 : 0);
						machine.output.pop();
						if (currentIters % 100 == 0) {
							if (currentIters > 1000 * maxIters) {
								return { std::to_string(i), "*** Free ***"};
							}
						}
					}
					else {
						if (currentIters > maxIters) {
							maxIters = currentIters;
						}
						break;
					}
				}
			}
		}

		return { "Part 1", "*** Free ***" };
	}
}
