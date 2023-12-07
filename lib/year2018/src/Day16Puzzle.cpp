#include <2018/Day16Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <cassert>

namespace TwentyEighteen {

	Day16Puzzle::Day16Puzzle() :
		core::PuzzleBase("Chronal Classification", 2018, 16) {

	}
	Day16Puzzle::~Day16Puzzle() {

	}


	void Day16Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day16Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::unordered_set<OpCodeType> Day16Puzzle::validOpCodeTypes(const OpCodeScenario& scenario)
	{
		std::unordered_set<OpCodeType> opCodeTypes;

		OpCodeComputer<4> computer;

		OpCode code
		{
			.code = OpCodeType::UNKNOWN,
			.A = scenario.a,
			.B = scenario.b,
			.C = scenario.c
		};

		for (int ci = 0; ci < (int)OpCodeType::COUNT; ++ci)
		{
			auto c = (OpCodeType)ci;

			computer.registers = scenario.before;

			code.code = c;

			computer.runOpCode(code);

			bool valid = true;
			for (std::size_t i = 0; i < 4; ++i)
			{
				if (scenario.after[i] != computer.registers[i])
				{
					valid = false;
					break;
				}
			}

			if (valid)
			{
				opCodeTypes.insert(c);
			}
		}

		return opCodeTypes;
	}

	std::pair<std::string, std::string> Day16Puzzle::fastSolve() {
		OpCodeComputer<4> computer;

		int part1 = 0;

		std::vector<OpCodeScenario> scenarios;
		std::vector<std::array<OpCodeNumber, 4>> instructions;
		std::unordered_map<OpCodeNumber, std::unordered_set<OpCodeType>> possibleOpCodeTypes;

		OpCodeScenario* curr{ nullptr };

		bool processingPart2 = false;

		for (const auto& l : m_InputLines)
		{
			if (l.empty()) { continue; }
				if (StringExtensions::startsWith(l, "Before: "))
				{
					scenarios.push_back({});
					curr = &scenarios.back();

					const auto& p = StringExtensions::splitStringByDelimeter(l, " ,[]");
					assert(p.size() == 5);

					curr->before[0] = (OpCodeNumber)std::stoll(p[1]);
					curr->before[1] = (OpCodeNumber)std::stoll(p[2]);
					curr->before[2] = (OpCodeNumber)std::stoll(p[3]);
					curr->before[3] = (OpCodeNumber)std::stoll(p[4]);
				}
				else if (StringExtensions::startsWith(l, "After: "))
				{

					const auto& p = StringExtensions::splitStringByDelimeter(l, " ,[]");
					assert(p.size() == 5);
					assert(curr != nullptr);

					curr->after[0] = (OpCodeNumber)std::stoll(p[1]);
					curr->after[1] = (OpCodeNumber)std::stoll(p[2]);
					curr->after[2] = (OpCodeNumber)std::stoll(p[3]);
					curr->after[3] = (OpCodeNumber)std::stoll(p[4]);

					curr = nullptr;
				}
				else
				{
					if (curr == nullptr)
					{
						const auto& p = StringExtensions::splitStringByDelimeter(l, " ");
						assert(p.size() == 4);
						instructions.push_back(
							{
								(OpCodeNumber)std::stoll(p[0]),
								(OpCodeNumber)std::stoll(p[1]),
								(OpCodeNumber)std::stoll(p[2]),
								(OpCodeNumber)std::stoll(p[3])
							});
						continue;
					}
					const auto& p = StringExtensions::splitStringByDelimeter(l, " ");
					assert(p.size() == 4);
					assert(curr != nullptr);

					curr->opcodeNumber = (OpCodeNumber)std::stoll(p[0]);
					curr->a = (OpCodeNumber)std::stoll(p[1]);
					curr->b = (OpCodeNumber)std::stoll(p[2]);
					curr->c = (OpCodeNumber)std::stoll(p[3]);
				}
			
		}

		for (const auto& s : scenarios)
		{
			const auto& validCodes = validOpCodeTypes(s);
			for (const auto& c : validCodes)
			{
				possibleOpCodeTypes[s.opcodeNumber].insert(c);
			}
			if (validCodes.size() >= 3)
			{
				part1++;
			}
		}

		OpCodeNumber part2 = 0;

		bool possibleToSolve = false;
		for (const auto& [num, codes] : possibleOpCodeTypes)
		{
			if (codes.size() == 1)
			{
				possibleToSolve = true;
				break;
			}
		}

		if (possibleToSolve)
		{
			std::unordered_set<OpCodeType> erased;
			int countdown = 0;
			bool solved = false;
			while (!solved)
			{
				std::size_t found = 0;
				for (const auto& [num, codes] : possibleOpCodeTypes)
				{
					if (codes.size() == 1)
					{
						found++;

						const auto code = *codes.begin();
						if (!erased.contains(code))
						{
							erased.insert(code);
							for (auto& [eraseNum, codesToEraseFrom] : possibleOpCodeTypes)
							{
								if (num == eraseNum) { continue; }
								codesToEraseFrom.erase(code);
							}
							break;
						}
					}
				}

				if (found == possibleOpCodeTypes.size())
				{
					solved = true;
				}

				countdown++;
				if (countdown > 10000)
				{
					return { std::to_string(part1), "Could not solve part 2 :("};
				}
			}


			for (const auto& [num, codes] : possibleOpCodeTypes)
			{
				assert(codes.size() == 1);
			}


			std::vector<OpCode> opCodes;
			for (const auto& instr : instructions)
			{
				opCodes.emplace_back(
					OpCode{
						.code = *possibleOpCodeTypes.at(instr[0]).begin(),
						.A = instr[1],
						.B = instr[2],
						.C = instr[3],
					});
			}


			computer.registers = { 0,0,0,0 };

			for (const auto& c : opCodes)
			{
				computer.runOpCode(c);
			}

			part2 = computer.registers[0];
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
