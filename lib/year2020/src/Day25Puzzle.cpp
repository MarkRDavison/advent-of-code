#include <2020/Day25Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>

namespace TwentyTwenty {
	
	Day25Puzzle::Day25Puzzle() :
		core::PuzzleBase("Combo Breaker", 2020, 25) {
	}


	void Day25Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day25Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day25Puzzle::fastSolve() {

		const uint64_t cardPublicKey = std::stol(m_InputLines[0]);
		const uint64_t doorPublicKey = std::stol(m_InputLines[1]);
		const uint64_t subjectNumber = 7;
		const uint64_t bigPrimeModulo = 20201227;
		uint64_t runningCard = 1;
		uint64_t runningDoor = 1;

        while (true) {
            runningCard *= subjectNumber;
            runningCard %= bigPrimeModulo;
            runningDoor *= cardPublicKey;
            runningDoor %= bigPrimeModulo;
            if (runningCard == doorPublicKey) {
                break;
            }
        }

		return { std::to_string(runningDoor), "There is no part 2!" };
	}
}
