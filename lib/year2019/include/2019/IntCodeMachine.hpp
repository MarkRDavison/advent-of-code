#pragma once

#include <vector>

namespace TwentyNineteen
{
	typedef long long IntCodeNumber;

	class IntCodeMachine
	{
	public:
		static constexpr const int OpCode_End = 99;
		static constexpr const int OpCode_Add = 1;
		static constexpr const int OpCode_Mul = 2;

		IntCodeMachine();
		IntCodeMachine(const std::vector<IntCodeNumber>& instructions);

		IntCodeNumber* pc{ nullptr };

		IntCodeNumber pcInternal{ 0 };

		std::vector<IntCodeNumber> instructions;

		bool programCounterInRange() const;

		bool runCurrentInstruction();

		void runTillEnd();
	};

}