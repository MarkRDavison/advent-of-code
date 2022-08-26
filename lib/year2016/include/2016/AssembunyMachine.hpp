#ifndef INCLUDED_ADVENT_OF_CODE_2016_ASSEMBUNY_MACHINE_HPP_
#define INCLUDED_ADVENT_OF_CODE_2016_ASSEMBUNY_MACHINE_HPP_

#include <string>
#include <vector>

namespace TwentySixteen {

	using AssembunnyInteger = long;
	using Registers = AssembunnyInteger[4];

	struct AssembunnyInstruction {
		std::string type;

		std::string arg1;
		std::string arg2;
	};

	class AssembunyMachine {
	public:
		AssembunyMachine(const std::vector<std::string>& _instructions);

		void applyInstructionAtPC();

		Registers registers{ 0 };
		AssembunnyInteger programCounter;
		std::vector<AssembunnyInstruction> instructions;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2016_ASSEMBUNY_MACHINE_HPP_