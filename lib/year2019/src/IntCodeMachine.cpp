#include <2019/IntCodeMachine.hpp>
#include <cassert>

namespace TwentyNineteen
{

	IntCodeMachine::IntCodeMachine() : IntCodeMachine(std::vector<IntCodeNumber>())
	{

	}
	IntCodeMachine::IntCodeMachine(const std::vector<IntCodeNumber>& instructions) :
		pc(&pcInternal),
		instructions(instructions)
	{

	}


	bool IntCodeMachine::programCounterInRange() const
	{
		return *pc >= 0 && *pc < (IntCodeNumber)instructions.size();
	}

	bool IntCodeMachine::runCurrentInstruction()
	{
		const auto opCode = instructions.at(*pc);

		if (opCode == OpCode_End)
		{
			return false;
		}

		const auto reg1 = (std::size_t)instructions.at(*pc + 1);
		const auto reg2 = (std::size_t)instructions.at(*pc + 2);
		const auto val1 = instructions.at(reg1);
		const auto val2 = instructions.at(reg2);
		const auto dest = (std::size_t)instructions.at(*pc + 3);

		if (opCode == OpCode_Add)
		{
			instructions[dest] = val1 + val2;
		}
		else if (opCode == OpCode_Mul)
		{
			instructions[dest] = val1 * val2;
		}
		else
		{
			assert(false);
		}

		*pc += 4;

		return true;
	}

	void IntCodeMachine::runTillEnd()
	{
		while (programCounterInRange())
		{
			if (!runCurrentInstruction())
			{
				break;
			}
		}
	}
}