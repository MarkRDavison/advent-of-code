#include <2017/Day18Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <map>
#include <queue>

#include <2017/Tablet.hpp>

#define PC '#'
#define SENT '%'

namespace TwentySeventeen {

	using IntegerType = int64_t;
	using Registers = std::map<char, IntegerType>;

	static bool isRegister(const std::string& _str) {
		return 'a' <= _str[0] && _str[0] <= 'z';
	}

	static IntegerType& getRegisterValue(std::map<char, IntegerType>& _registers, const std::string& _register) {
		return _registers[_register[0]];
	}

	struct Instruction {
		std::string type;

		std::string arg1;
		std::string arg2;
	};

	static bool runInstruction(const Instruction& _instr, IntegerType& _pc, Registers& _registers, std::queue<IntegerType>& _receive, std::queue<IntegerType>& _send, bool _part1) {
		if (_instr.type == "set") {
			IntegerType value;
			if (isRegister(_instr.arg2)) {
				value = getRegisterValue(_registers, _instr.arg2);
			}
			else {
				value = std::stoi(_instr.arg2);
			}
			auto& regValue = getRegisterValue(_registers, _instr.arg1);
			regValue = value;
		}
		else if (_instr.type == "add") {
			IntegerType value;
			if (isRegister(_instr.arg2)) {
				value = getRegisterValue(_registers, _instr.arg2);
			}
			else {
				value = std::stoi(_instr.arg2);
			}
			auto& regValue = getRegisterValue(_registers, _instr.arg1);
			regValue += value;
		}
		else if (_instr.type == "mul") {
			IntegerType value;
			if (isRegister(_instr.arg2)) {
				value = getRegisterValue(_registers, _instr.arg2);
			}
			else {
				value = std::stoi(_instr.arg2);
			}
			auto& regValue = getRegisterValue(_registers, _instr.arg1);
			regValue *= value;
		}
		else if (_instr.type == "mod") {
			IntegerType value;
			if (isRegister(_instr.arg2)) {
				value = getRegisterValue(_registers, _instr.arg2);
			}
			else {
				value = std::stoi(_instr.arg2);
			}
			auto& regValue = getRegisterValue(_registers, _instr.arg1);
			regValue %= value;
		}
		else if (_instr.type == "snd") {
			IntegerType value;
			if (isRegister(_instr.arg1)) {
				value = getRegisterValue(_registers, _instr.arg1);
			}
			else {
				value = std::stoi(_instr.arg1);
			}
			if (_part1) {
				_receive.push(value);
			}
			else {
				_registers['?']++;
				_send.push(value);
			}
		}
		else if (_instr.type == "rcv") {
			IntegerType value;
			if (isRegister(_instr.arg1)) {
				value = getRegisterValue(_registers, _instr.arg1);
			}
			else {
				value = std::stoi(_instr.arg1);
			}

			if (!_part1) {
				if (_receive.empty()) {
					return false;
				}
				const auto soundVal = _receive.front();
				_receive.pop();
				getRegisterValue(_registers, _instr.arg1) = soundVal;
			}
			else if (value != 0) {
				if (_receive.empty()) {
					return false;
				}
				const auto soundVal = _receive.front();
				_receive.pop();
			}

		}
		else if (_instr.type == "jgz") {
			IntegerType value1;
			IntegerType value2;
			if (isRegister(_instr.arg1)) {
				value1 = getRegisterValue(_registers, _instr.arg1);
			}
			else {
				value1 = std::stoi(_instr.arg1);
			}
			if (isRegister(_instr.arg2)) {
				value2 = getRegisterValue(_registers, _instr.arg2);
			}
			else {
				value2 = std::stoi(_instr.arg2);
			}
			if (value1 > 0) {
				_pc += value2;
				return true;
			}
		}

		_pc++;
		return true;
	}

	Day18Puzzle::Day18Puzzle() :
		core::PuzzleBase("Duet", 2017, 18) {

	}
	Day18Puzzle::~Day18Puzzle() {

	}


	void Day18Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day18Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}


	std::pair<std::string, std::string> Day18Puzzle::fastSolve() {
		IntegerType part1 = 0;
		std::vector<Instruction> instructions;
		for (const auto& instr : m_InputLines) {
			const auto& splits = StringExtensions::splitStringByDelimeter(instr, " ");

			auto& instruction = instructions.emplace_back();
			instruction.type = splits[0];
			instruction.arg1 = splits[1];
			if (splits.size() > 2) {
				instruction.arg2 = splits[2];
			}
		}
			
		std::queue<IntegerType> sounds;

		IntegerType pc = 0;
		std::map<char, IntegerType> registers;
		while (pc >= 0 && pc < instructions.size()) {
			const auto& instr = instructions[pc];

			bool hasSound = !sounds.empty();
			part1 = hasSound
				? sounds.front()
				: 0;

			runInstruction(instr, pc, registers, sounds, sounds, true);

			if (hasSound && sounds.empty()) {
				break;
			}
		}

		Tablet tablet0(m_InputLines);
		Tablet tablet1(m_InputLines);

		std::queue<IntegerType> sounds0;
		std::queue<IntegerType> sounds1;

		tablet0.registers.emplace('p', 0);
		tablet0.registers.emplace(PC, 0);

		tablet1.registers.emplace('p', 1);
		tablet1.registers.emplace(PC, 0);

		while (true) {
			if (!tablet0.run(sounds0, sounds1)) {
				break;
			}
			if (!tablet1.run(sounds1, sounds0)) {
				break;
			}

			if (sounds0.empty() && sounds1.empty()) {
				break;
			}
		}

		return { std::to_string(part1), std::to_string(tablet1.registers[SENT]) };
	}
}
