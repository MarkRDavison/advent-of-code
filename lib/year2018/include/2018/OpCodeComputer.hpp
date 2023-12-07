#pragma once

#include <cstdint>
#include <array>
#include <unordered_map>
#include <functional>

namespace TwentyEighteen
{
	typedef long long OpCodeNumber;

	enum class OpCodeType
	{
		UNKNOWN = -1,
		ADDR = 0,
		ADDI = 1,
		MULR = 2,
		MULI = 3,
		BANR = 4,
		BANI = 5,
		BORR = 6,
		BORI = 7,
		SETR = 8,
		SETI = 9,
		GTIR = 10,
		GTRI = 11,
		GTRR = 12,
		EQIR = 13,
		EQRI = 14,
		EQRR = 15,

		COUNT = 16
	};

	struct OpCode
	{
		OpCodeType code{ OpCodeType::UNKNOWN };
		OpCodeNumber A{ 0 };
		OpCodeNumber B{ 0 };
		OpCodeNumber C{ 0 };
	};

	template<OpCodeNumber N>
	class OpCodeComputer
	{
	public:
		OpCodeComputer()
		{
			instructions = {
				{
					OpCodeType::ADDR,
					[](const OpCode& code, std::array<OpCodeNumber, N>& reg) -> void
					{
						reg[code.C] = reg[code.A] + reg[code.B];
					}
				},
				{
					OpCodeType::ADDI,
					[](const OpCode& code, std::array<OpCodeNumber, N>& reg) -> void
					{
						reg[code.C] = reg[code.A] + code.B;
					}
				},
				{
					OpCodeType::MULR,
					[](const OpCode& code, std::array<OpCodeNumber, N>& reg) -> void
					{
						reg[code.C] = reg[code.A] * reg[code.B];
					}
				},
				{
					OpCodeType::MULI,
					[](const OpCode& code, std::array<OpCodeNumber, N>& reg) -> void
					{
						reg[code.C] = reg[code.A] * code.B;
					}
				},
				{
					OpCodeType::BANR,
					[](const OpCode& code, std::array<OpCodeNumber, N>& reg) -> void
					{
						reg[code.C] = reg[code.A] & reg[code.B];
					}
				},
				{
					OpCodeType::BANI,
					[](const OpCode& code, std::array<OpCodeNumber, N>& reg) -> void
					{
						reg[code.C] = reg[code.A] & code.B;
					}
				},
				{
					OpCodeType::BORR,
					[](const OpCode& code, std::array<OpCodeNumber, N>& reg) -> void
					{
						reg[code.C] = reg[code.A] | reg[code.B];
					}
				},
				{
					OpCodeType::BORI,
					[](const OpCode& code, std::array<OpCodeNumber, N>& reg) -> void
					{
						reg[code.C] = reg[code.A] | code.B;
					}
				},
				{
					OpCodeType::SETR,
					[](const OpCode& code, std::array<OpCodeNumber, N>& reg) -> void
					{
						reg[code.C] = reg[code.A];
					}
				},
				{
					OpCodeType::SETI,
					[](const OpCode& code, std::array<OpCodeNumber, N>& reg) -> void
					{
						reg[code.C] = code.A;
					}
				},
				{
					OpCodeType::GTIR,
					[](const OpCode& code, std::array<OpCodeNumber, N>& reg) -> void
					{
						reg[code.C] = code.A > reg[code.B] ? 1 : 0;
					}
				},
				{
					OpCodeType::GTRI,
					[](const OpCode& code, std::array<OpCodeNumber, N>& reg) -> void
					{
						reg[code.C] = reg[code.A] > code.B ? 1 : 0;
					}
				},
				{
					OpCodeType::GTRR,
					[](const OpCode& code, std::array<OpCodeNumber, N>& reg) -> void
					{
						reg[code.C] = reg[code.A] > reg[code.B] ? 1 : 0;
					}
				},
				{
					OpCodeType::EQIR,
					[](const OpCode& code, std::array<OpCodeNumber, N>& reg) -> void
					{
						reg[code.C] = code.A == reg[code.B] ? 1 : 0;
					}
				},
				{
					OpCodeType::EQRI,
					[](const OpCode& code, std::array<OpCodeNumber, N>& reg) -> void
					{
						reg[code.C] = reg[code.A] == code.B ? 1 : 0;
					}
				},
				{
					OpCodeType::EQRR,
					[](const OpCode& code, std::array<OpCodeNumber, N>& reg) -> void
					{
						reg[code.C] = reg[code.A] == reg[code.B] ? 1 : 0;
					}
				}
			};
		}

		void runOpCode(const OpCode& code)
		{
			instructions[code.code](code, registers);
		}

		std::array<OpCodeNumber, N> registers;

		std::unordered_map<OpCodeType, std::function<void(const OpCode&, std::array<OpCodeNumber, N>&)>> instructions;
	};
}