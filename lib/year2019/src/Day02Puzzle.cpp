#include <2019/Day02Puzzle.hpp>
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

		std::size_t pc = 0;

		while (pc < nums.size())
		{
			const auto opCode = nums.at(pc);

			if (opCode == 99) { break; }

			const auto reg1 = (std::size_t)nums.at(pc + 1);
			const auto reg2 = (std::size_t)nums.at(pc + 2);
			const auto val1 = nums.at(reg1);
			const auto val2 = nums.at(reg2);
			const auto dest = (std::size_t)nums.at(pc + 3);

			if (opCode == 1)
			{
				nums[dest] = val1 + val2;
			}
			else if (opCode == 2)
			{
				nums[dest] = val1 * val2;
			}
			else
			{
				assert(false);
			}

			pc += 4;
		}

		return { std::to_string(nums.at(0)), "Part 2" };
	}
}
