#include <2017/Day25Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <unordered_map>

namespace TwentySeventeen {

	using ChecksumNumber = int64_t;
	
	Day25Puzzle::Day25Puzzle() :
		core::PuzzleBase("The Halting Problem", 2017, 25) {

	}
	Day25Puzzle::~Day25Puzzle() {

	}


	void Day25Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByLines(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0])));
	}

	void Day25Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct Process {
		ChecksumNumber zero_writeValue;
		ChecksumNumber zero_moveOffset;
		char zero_nextState;

		ChecksumNumber one_writeValue;
		ChecksumNumber one_moveOffset;
		char one_nextState;
	};

	std::pair<std::string, std::string> Day25Puzzle::fastSolve() {

		const auto startState = ze::StringExtensions::splitStringByDelimeter(m_InputLines[0], " .")[3][0];

		const auto checkSumStep = (ChecksumNumber)std::stoull(ze::StringExtensions::splitStringByDelimeter(m_InputLines[1], " .")[5]);

		std::unordered_map<char, Process> processes;
		std::unordered_map<ChecksumNumber, ChecksumNumber> tape;

		for (std::size_t i = 3; i < m_InputLines.size(); i += 10) {
			const auto state = ze::StringExtensions::splitStringByDelimeter(m_InputLines[i + 0], " .:")[2][0];

			const auto writeIfZero = ze::StringExtensions::splitStringByDelimeter(m_InputLines[i + 2], " .:-")[3];
			const auto moveOffsetIfZero = ze::StringExtensions::splitStringByDelimeter(m_InputLines[i + 3], " .:-")[5] == "left" ? -1 : +1;
			const auto nextStateIfZero = ze::StringExtensions::splitStringByDelimeter(m_InputLines[i + 4], " .:-")[3][0];

			const auto writeIfOne = ze::StringExtensions::splitStringByDelimeter(m_InputLines[i + 6], " .:-")[3];
			const auto moveOffsetIfOne = ze::StringExtensions::splitStringByDelimeter(m_InputLines[i + 7], " .:-")[5] == "left" ? -1 : +1;
			const auto nextStateIfOne = ze::StringExtensions::splitStringByDelimeter(m_InputLines[i + 8], " .:-")[3][0];

			auto& currentProcess = processes[state];
			currentProcess.zero_writeValue = std::stoll(writeIfZero);
			currentProcess.zero_moveOffset = moveOffsetIfZero;
			currentProcess.zero_nextState = nextStateIfZero;

			currentProcess.one_writeValue = std::stoll(writeIfOne);
			currentProcess.one_moveOffset = moveOffsetIfOne;
			currentProcess.one_nextState = nextStateIfOne;
		}

		ChecksumNumber pc{ 0 };
		char state = startState;

		ChecksumNumber part1 = 0;

		for (ChecksumNumber i = 0; i < checkSumStep; ++i) {
			const auto& process = processes[state];
			auto& tapeValue = tape[pc];
			if (tapeValue == 1) {
				part1--;
			}
			if (tapeValue == 0) {
				tapeValue = process.zero_writeValue;
				pc += process.zero_moveOffset;
				state = process.zero_nextState;
			}
			else {
				tapeValue = process.one_writeValue;
				pc += process.one_moveOffset;
				state = process.one_nextState;
			}
			if (tapeValue == 1) {
				part1++;
			}

			if (getVerbose()) {
				for (ChecksumNumber pi = pc - 3; pi <= pc + 3; ++pi) {
					std::cout << tape[pi] << " ";
				}
				std::cout << "\tPC: " << pc << ", next state: " << state << std::endl;
			}
		}

		return { std::to_string(part1), "*** Free ***"};
	}
}
