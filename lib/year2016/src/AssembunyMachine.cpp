#include <2016/AssembunyMachine.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>

namespace TwentySixteen {

	static bool isRegister(const std::string& _str) {
		return 'a' <= _str[0] && _str[0] <= 'd';
	}
	static long& getRegisterValue(Registers& _registers, const std::string& _register) {
		const auto reg = (unsigned)(_register[0] - 'a');
		return _registers[reg];
	}

	AssembunyMachine::AssembunyMachine(const std::vector<std::string>& _instructions) :
		programCounter(0) {

		for (const auto& instr : _instructions) {
			const auto& splits = ze::StringExtensions::splitStringByDelimeter(instr, " ");

			auto& instruction = instructions.emplace_back();
			instruction.type = splits[0];
			instruction.arg1 = splits[1];
			if (splits.size() > 2) {
				instruction.arg2 = splits[2];
			}
		}
	}

	void AssembunyMachine::applyInstructionAtPC() {
		auto& instruction = instructions[programCounter];

		if (instruction.type == "cpy") {
			long value;
			if (isRegister(instruction.arg1)) {
				value = getRegisterValue(registers, instruction.arg1);
			}
			else {
				value = std::stoi(instruction.arg1);
			}
			auto& regValue = getRegisterValue(registers, instruction.arg2);
			regValue = value;
		}
		else if (instruction.type == "inc") {
			auto& regValue = getRegisterValue(registers, instruction.arg1);
			regValue++;
		}
		else if (instruction.type == "dec") {
			auto& regValue = getRegisterValue(registers, instruction.arg1);
			regValue--;
		}
		else if (instruction.type == "jnz") {
			long value1;
			if (isRegister(instruction.arg1)) {
				value1 = getRegisterValue(registers, instruction.arg1);
			}
			else {
				value1 = std::stoi(instruction.arg1);
			}
			if (value1 != 0) {
				long value2;
				if (isRegister(instruction.arg2)) {
					value2 = getRegisterValue(registers, instruction.arg2);
				}
				else {
					value2 = std::stoi(instruction.arg2);
				}
				programCounter += value2;
				return;
			}
		}
		else if (instruction.type == "tgl") {
			long value;
			if (isRegister(instruction.arg1)) {
				value = getRegisterValue(registers, instruction.arg1);
			}
			else {
				value = std::stoi(instruction.arg1);
			}

			auto toggledPc = programCounter + value;

			if (toggledPc < instructions.size()) {
				auto& instructionToToggle = instructions[toggledPc];

				if (instructionToToggle.type == "tgl" ||
					instructionToToggle.type == "dec") {
					instructionToToggle.type = "inc";
				}
				else if (instructionToToggle.type == "inc") {
					instructionToToggle.type = "dec";
				}
				else if (instructionToToggle.type == "cpy") {
					instructionToToggle.type = "jnz";
				}
				else if (instructionToToggle.type == "jnz") {
					instructionToToggle.type = "cpy";
				}
				else {
					std::string msg = "Unhandled instruction type to toggle " + instructionToToggle.type;
					throw std::exception(msg.c_str());
				}
			}

		}
		else {
			std::string msg = "Unhandled instruction type " + instruction.type;
			throw std::exception(msg.c_str());
		}
		programCounter++;
	}
}