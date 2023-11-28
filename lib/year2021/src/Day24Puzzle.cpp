#include <2021/Day24Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <stack>
#include <array>
#include <cassert>
#include <unordered_set>


namespace TwentyTwentyOne {

	bool isVariable(const std::string& _str) {
		if ('1' <= _str.front() && _str.front() <= '9' || '-' == _str.front()) {
			return false;
		}

		return true;
	}

	void load1(const std::string& _str, Instruction& _instr) {
		_instr.is1Var = isVariable(_str);
		if (_instr.is1Var) {
			_instr.var1 = _str.front();
		}
		else {
			_instr.val1 = (AluNumber)std::stol(_str);
		}
	}

	void load2(const std::string& _str, Instruction& _instr) {
		_instr.is2Var = isVariable(_str);
		if (_instr.is2Var) {
			_instr.var2 = _str.front();
		}
		else {
			_instr.val2 = (AluNumber)std::stol(_str);
		}
	}

	ArithmeticLogicUnit::ArithmeticLogicUnit(const std::vector<std::string>& _input) : ArithmeticLogicUnit(_input, {}) {}
	ArithmeticLogicUnit::ArithmeticLogicUnit(const std::vector<std::string>& _input, const std::vector<AluNumber>& _inputValues) : m_InputValues(_inputValues) {
		for (const auto& i : _input) {
			const auto& parts = StringExtensions::splitStringByDelimeter(i, " ");

			auto& instr = m_Instructions.emplace_back();

			if (parts[0] == "inp") {
				instr.type = Instruction::Type::inp;
				instr.var1 = parts[1].front();
			}
			else if (parts[0] == "add") {
				instr.type = Instruction::Type::add;
				load1(parts[1], instr);
				load2(parts[2], instr);
			}
			else if (parts[0] == "mul") {
				instr.type = Instruction::Type::mul;
				load1(parts[1], instr);
				load2(parts[2], instr);
			}
			else if (parts[0] == "div") {
				instr.type = Instruction::Type::div;
				load1(parts[1], instr);
				load2(parts[2], instr);
			}
			else if (parts[0] == "mod") {
				instr.type = Instruction::Type::mod;
				load1(parts[1], instr);
				load2(parts[2], instr);
			}
			else if (parts[0] == "eql") {
				instr.type = Instruction::Type::eql;
				load1(parts[1], instr);
				load2(parts[2], instr);
			}
			else {
				assert(false && "invalid operation");
			}
		}

		reset(_inputValues);
	}

	void ArithmeticLogicUnit::run() {
		for (const auto& instruction : m_Instructions) {
			switch (instruction.type) {
			case Instruction::Type::inp:
				runInp(instruction);
				break;
			case Instruction::Type::add:
				runAdd(instruction);
				break;
			case Instruction::Type::mul:
				runMul(instruction);
				break;
			case Instruction::Type::div:
				runDiv(instruction);
				break;
			case Instruction::Type::mod:
				runMod(instruction);
				break;
			case Instruction::Type::eql:
				runEql(instruction);
				break;
			}
		}
	}
	void ArithmeticLogicUnit::reset(const std::vector<AluNumber>& _inputValues) {
		m_Values.clear();

		m_Values['w'] = 0;
		m_Values['x'] = 0;
		m_Values['y'] = 0;
		m_Values['z'] = 0;

		m_InputValues = _inputValues;
	}

	void ArithmeticLogicUnit::runInp(const Instruction& _instruction) {
		const auto val = m_InputValues.front();
		m_InputValues.erase(m_InputValues.begin(), m_InputValues.begin() + 1);

		m_Values[_instruction.var1] = val;
	}
	void ArithmeticLogicUnit::runAdd(const Instruction& _instruction) {
		m_Values[_instruction.var1] = get1(_instruction) + get2(_instruction);
	}
	void ArithmeticLogicUnit::runMul(const Instruction& _instruction) {
		m_Values[_instruction.var1] = get1(_instruction) * get2(_instruction);
	}
	void ArithmeticLogicUnit::runDiv(const Instruction& _instruction) {
		assert(get2(_instruction) != 0 && "Cannot divide by zero");
		m_Values[_instruction.var1] = get1(_instruction) / get2(_instruction);
	}
	void ArithmeticLogicUnit::runMod(const Instruction& _instruction) {
		m_Values[_instruction.var1] = get1(_instruction) % get2(_instruction);
	}
	void ArithmeticLogicUnit::runEql(const Instruction& _instruction) {
		auto equal = get1(_instruction) == get2(_instruction);
		m_Values[_instruction.var1] = equal ? 1 : 0;
	}

	AluNumber ArithmeticLogicUnit::get1(const Instruction& _instruction) const {
		if (_instruction.is1Var) {
			return get(_instruction.var1);
		}
		return _instruction.val1;
	}
	AluNumber ArithmeticLogicUnit::get2(const Instruction& _instruction) const {
		if (_instruction.is2Var) {
			return get(_instruction.var2);
		}
		return _instruction.val2;
	}

	AluNumber ArithmeticLogicUnit::get(char _name) const {
		return m_Values.at(_name);
	}

	Day24Puzzle::Day24Puzzle() :
		core::PuzzleBase("Arithmetic Logic Unit", 2021, 24) {
	}


	void Day24Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day24Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day24Puzzle::fastSolve() {
		unsigned i = 0; 
		unsigned sec = 0;
		unsigned secIndex = 0;
		std::unordered_map<unsigned, std::unordered_set < std::string> > sectionCount;
		std::vector<std::pair<AluNumber, AluNumber>> checkOffsets(14);
		do {
			if (m_InputLines[i] == "inp w") {
				sec++;
				secIndex = 0;
			}
			if (secIndex == 5) {
				checkOffsets[sec-1].first = (AluNumber)std::stol(StringExtensions::splitStringByDelimeter(m_InputLines[i], " ").back());
			}
			if (secIndex == 15) {
				checkOffsets[sec-1].second = (AluNumber)std::stol(StringExtensions::splitStringByDelimeter(m_InputLines[i], " ").back());
			}
			sectionCount[secIndex++].insert(m_InputLines[i]);

			i++;
		} while (i < m_InputLines.size());

		std::stack<std::pair<int, int>> indexValueStack;
		std::vector<std::pair<std::pair<int, int>, int>> prereqs;

		i = 0;
		for (const auto& [check, offset] : checkOffsets) {

			if (check <= 0) {
				// pop
				assert(!indexValueStack.empty());
				const auto top = indexValueStack.top();
				indexValueStack.pop();

				auto overflow = top.second + check;

				int lhs;
				int rhs;
				if (overflow < 0) {
					lhs = i;
					rhs = top.first;
				}
				else {
					rhs = i;
					lhs = top.first;
				}

				prereqs.emplace_back(
					std::pair<int, int>{ rhs, lhs },
					std::abs(overflow)
				);
			}
			else {
				// push
				indexValueStack.emplace(i, offset);
			}

			i++;
		}

		assert(indexValueStack.empty());

		std::array<int, 14> largest;
		std::array<int, 14> smallest;
		i = 0;
		for (const auto& [indecies, offset] : prereqs) {
			largest[indecies.first] = 9;
			largest[indecies.second] = 9 - offset;

			smallest[indecies.first] = 1 + offset;
			smallest[indecies.second] = 1;

			i++;
		}

		std::string part1;
		std::string part2;
		for (const auto v : largest) {
			part1 += std::to_string(v);
		}

		for (const auto v : smallest) {
			part2 += std::to_string(v);
		}

		return { part1, part2 };
	}
}
