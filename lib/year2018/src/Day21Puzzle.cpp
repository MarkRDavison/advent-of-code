#include <2018/Day21Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <2018/OpCodeComputer.hpp>
#include <unordered_set>

namespace TwentyEighteen {
	
	Day21Puzzle::Day21Puzzle() :
		core::PuzzleBase("Chronal Conversion", 2018, 21) {

	}
	Day21Puzzle::~Day21Puzzle() {

	}


	void Day21Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day21Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day21Puzzle::fastSolve() {
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

		OpCodeNumber part1 = -1;
		OpCodeNumber last;
		std::unordered_set<OpCodeNumber> seen;

		{
			OpCodeComputer<6> computer;
			computer.registers = { 0,0,0,0,0,0 };
			OpCodeNumber& pc = computer.registers[pcRegisterIndex];

			while (0 <= pc && pc < (OpCodeNumber)instructions.size())
			{
				const auto& instr = instructions[pc];

				computer.runOpCode(instr);

				pc++;

				if (instr.code == OpCodeType::EQRR && instr.B == 0)
				{
					if (part1 == -1)
					{
						part1 = computer.registers[1];
					}
					if (seen.contains(computer.registers[1]))
					{
						break;
					}
					if (seen.size() % 100 == 0)
					{
						std::cout << "seen size: " << seen.size() << ", this took until there were 15500 entries on my input " << std::endl;
					}
					last = computer.registers[1];
					seen.insert(last);
				}

			}
		}


		return { std::to_string(part1), std::to_string(last) };
	}
}
