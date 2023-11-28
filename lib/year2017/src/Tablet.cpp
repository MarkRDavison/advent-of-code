#include <2017/Tablet.hpp>
#include <Core/StringExtensions.hpp>

#define PC '#'
#define SENT '%'
#define MUL 'M'

namespace TwentySeventeen {

	static TabletIntegerType getValue(TabletRegisters& _registers, const std::string& _registerOrValue) {
		if ('a' <= _registerOrValue[0] && _registerOrValue[0] <= 'z') {
			return _registers[_registerOrValue[0]];
		}
		return (TabletIntegerType)std::stoull(_registerOrValue);
	}

	Tablet::Tablet(const std::vector<std::string>& _input) {
		for (const auto& instr : _input) {
			const auto& splits = StringExtensions::splitStringByDelimeter(instr, " ");

			auto& instruction = instructions.emplace_back();
			instruction.type = splits[0];
			instruction.arg1 = splits[1];
			if (splits.size() > 2) {
				instruction.arg2 = splits[2];
			}
		}
	}

	bool Tablet::run(std::queue<TabletIntegerType>& _queueIn, std::queue<TabletIntegerType>& _queueOut) {

		while (registers[PC] >= 0 && registers[PC] < (TabletIntegerType)instructions.size()) {
			const auto& instr = instructions[registers[PC]];

			if (instr.type == "rcv") {
				if (_queueIn.empty()) {
					return true;
				}
				registers[instr.arg1[0]] = _queueIn.front();
				_queueIn.pop();
			}
			else if (instr.type == "jgz") {
				if (getValue(registers, instr.arg1) > 0) {
					registers[PC] += getValue(registers, instr.arg2);
					continue;
				}
			}
			else if (instr.type == "jnz") {
				if (getValue(registers, instr.arg1) != 0) {
					registers[PC] += getValue(registers, instr.arg2);
					continue;
				}
			}
			else if (instr.type == "snd") {
				_queueOut.push(getValue(registers, instr.arg1));
				registers[SENT]++;
			}
			else if (instr.type == "set") {
				registers[instr.arg1[0]] = getValue(registers, instr.arg2);
			}
			else if (instr.type == "add") {
				registers[instr.arg1[0]] = getValue(registers, instr.arg1) + getValue(registers, instr.arg2);
			}
			else if (instr.type == "sub") {
				registers[instr.arg1[0]] = getValue(registers, instr.arg1) - getValue(registers, instr.arg2);
			}
			else if (instr.type == "mul") {
				registers[MUL]++;
				registers[instr.arg1[0]] = getValue(registers, instr.arg1) * getValue(registers, instr.arg2);
			}
			else if (instr.type == "mod") {
				registers[instr.arg1[0]] = getValue(registers, instr.arg1) % getValue(registers, instr.arg2);
			}

			registers[PC]++;
		}

		return false;
	}

}