#include <2018/Day19Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <2018/OpCodeComputer.hpp>

namespace TwentyEighteen {
	
	Day19Puzzle::Day19Puzzle() :
		core::PuzzleBase("Go With The Flow", 2018, 19) {

	}
	Day19Puzzle::~Day19Puzzle() {

	}


	void Day19Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day19Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day19Puzzle::fastSolve() {
		const OpCodeNumber pcRegisterIndex = (OpCodeNumber)std::stoll(StringExtensions::splitStringByDelimeter(m_InputLines[0], " ")[1]);

		std::vector<OpCode> instructions;

		const std::unordered_map<std::string, OpCodeType> opcodes = {
			{ "addr", OpCodeType::ADDR },
			{ "addi", OpCodeType::ADDI },
			{ "mulr", OpCodeType::MULR },
			{ "muli", OpCodeType::MULI },
			{ "banr", OpCodeType::BANR },
			{ "bani", OpCodeType::BANI },
			{ "borr", OpCodeType::BORR },
			{ "bori", OpCodeType::BORI },
			{ "setr", OpCodeType::SETR },
			{ "seti", OpCodeType::SETI },
			{ "gtir", OpCodeType::GTIR },
			{ "gtri", OpCodeType::GTRI },
			{ "gtrr", OpCodeType::GTRR },
			{ "eqir", OpCodeType::EQIR },
			{ "eqri", OpCodeType::EQRI },
			{ "eqrr", OpCodeType::EQRR }
		};

		OpCodeComputer<6> computer;
		computer.registers = { 0,0,0,0,0,0 };
		OpCodeNumber& pc = computer.registers[pcRegisterIndex];

		for (std::size_t i = 1; i < m_InputLines.size(); ++i)
		{
			const auto& parts = StringExtensions::splitStringByDelimeter(m_InputLines[i], " ");

			instructions.emplace_back(
				OpCode{
					.code = opcodes.at(parts[0]),
					.A = (OpCodeNumber)std::stoll(parts[1]),
					.B = (OpCodeNumber)std::stoll(parts[2]),
					.C = (OpCodeNumber)std::stoll(parts[3])
				});
		}

		while (0 <= pc && pc < (OpCodeNumber)instructions.size())
		{
			const auto& instr = instructions[pc];

			computer.runOpCode(instr);

			pc++;
		}

		OpCodeNumber part1 = computer.registers[0];
		OpCodeNumber part2 = 0;

		computer.registers = { 1,0,0,0,0,0 };

		OpCodeNumber lastPc = pc;

		while (0 <= pc && pc < (OpCodeNumber)instructions.size())
		{
			const auto& instr = instructions[pc];

			computer.runOpCode(instr);

			pc++;

			if (pc > lastPc)
			{
				lastPc = pc;
			}
			else
			{
				break;
			}
		}

		const auto largeNum = *std::max_element(computer.registers.begin(), computer.registers.end());
			
		for (OpCodeNumber x = 1; x <= largeNum; ++x)
		{
			if (largeNum % x == 0)
			{
				part2 += x;
			}
		}

		return { std::to_string(part1), std::to_string(part2)};
	}
}
