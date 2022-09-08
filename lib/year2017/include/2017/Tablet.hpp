#ifndef INCLUDED_ADVENT_OF_CODE_2017_TABLET_HPP_
#define INCLUDED_ADVENT_OF_CODE_2017_TABLET_HPP_

#include <map>
#include <queue>
#include <Core/PuzzleBase.hpp>

namespace TwentySeventeen {

	using TabletIntegerType = int64_t;
	using TabletRegisters = std::map<char, TabletIntegerType>;

	struct TabletInstruction {
		std::string type;

		std::string arg1;
		std::string arg2;
	};

	class Tablet {
	public:
		Tablet(const std::vector<std::string>& _input);

		bool run(std::queue<TabletIntegerType>& _queueIn, std::queue<TabletIntegerType>& _queueOut);

		TabletRegisters registers;

		std::vector<TabletInstruction> instructions;
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_2017_TABLET_HPP_