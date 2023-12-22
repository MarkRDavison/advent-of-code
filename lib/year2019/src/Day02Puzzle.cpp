#include <2019/Day02Puzzle.hpp>
#include <2019/IntCodeMachine.hpp>
#include <Core/StringExtensions.hpp>
#include <cassert>

namespace TwentyNineteen {
	
	Day02Puzzle::Day02Puzzle() :
		core::PuzzleBase("1202 Program Alarm", 2019, 2) {

	}
	Day02Puzzle::~Day02Puzzle() {

	}


	void Day02Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day02Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day02Puzzle::fastSolve() 
	{
		return fastSolve(true);
	}
	std::pair<std::string, std::string> Day02Puzzle::fastSolve(bool gravityAssistOn)
	{
		auto nums = StringExtensions::splitLineToNumbers<long long>(m_InputLines[0], ",");

		if (gravityAssistOn)
		{
			nums[1] = 12;
			nums[2] = 2;
		}

		IntCodeNumber part1 = 0;
		IntCodeNumber part2 = 0;

		{
			IntCodeMachine machine(nums);
			machine.runTillEnd();

			part1 = machine.instructions[0];
		}
		constexpr IntCodeNumber Target = 19690720;

		if (gravityAssistOn)
		{
			for (IntCodeNumber noun = 0; noun <= 99; ++noun)
			{
				for (IntCodeNumber verb = 0; verb <= 99; ++verb)
				{
					IntCodeMachine machine(nums);
					machine.instructions[1] = noun;
					machine.instructions[2] = verb;
					machine.runTillEnd();

					if (machine.instructions[0] == Target)
					{
						part2 = 100 * noun + verb;
						return { std::to_string(part1), std::to_string(part2) };
					}
				}
			}
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
