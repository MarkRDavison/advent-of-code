#include <2016/Day21Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <algorithm>
#include <cassert>

namespace TwentySixteen {
	
	Day21Puzzle::Day21Puzzle() :
		core::PuzzleBase("Scrambled Letters and Hash", 2016, 21) {

	}
	Day21Puzzle::~Day21Puzzle() {

	}


	void Day21Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day21Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day21Puzzle::fastSolve() {
		const std::string password = "abcdefgh";
		const std::string scrambled = "fbgdceah";
		return fastSolve(password, scrambled);
	}

	static std::string solve(const std::vector<Instruction>& _instructions, const std::string& _startingPassword) {
		auto password(_startingPassword);
		for (const auto& instr : _instructions) {
			password = Day21Puzzle::apply(instr, password);
		}
		return password;
	}

	std::pair<std::string, std::string> Day21Puzzle::fastSolve(const std::string& _startingPassword, const std::string& _endingPasword) {
		std::vector<Instruction> instructions;

		for (const auto& line : m_InputLines) {
			instructions.push_back(parse(line));
		}

		std::string password1 = solve(instructions, _startingPassword);
		std::string password2(_endingPasword);

		std::sort(password2.begin(), password2.end());
		do {
			if (solve(instructions, password2) == _endingPasword) {
				break;
			}
		} while (std::next_permutation(password2.begin(), password2.end()));


		return { password1, password2 };
	}

	Instruction Day21Puzzle::parse(const std::string& _input) {
		const auto& parts = ze::StringExtensions::splitStringByDelimeter(_input, " ");


		if (parts[0] == "swap" && parts[1] == "position") {
			Instruction instr(InstructionType::SwapPosition);
			instr.fromPosition = std::stoi(parts[2]);
			instr.toPosition = std::stoi(parts[5]);
			return instr;
		}
		if (parts[0] == "swap" && parts[1] == "letter") {
			Instruction instr(InstructionType::SwapLetter);
			instr.fromLetter = parts[2].front();
			instr.toLetter = parts[5].front();
			return instr;
		}
		if (parts[0] == "reverse" && parts[1] == "positions") {
			Instruction instr(InstructionType::ReversePositions);
			instr.fromPosition = std::stoi(parts[2]);
			instr.toPosition = std::stoi(parts[4]);
			return instr;
		}
		if (parts[0] == "rotate" && (parts[1] == "left" || parts[1] == "right")) {
			Instruction instr(InstructionType::Rotate);
			instr.steps = std::stoi(parts[2]) * (parts[1] == "left" ? -1 : +1);
			return instr;
		}
		if (parts[0] == "move" && parts[1] == "position") {
			Instruction instr(InstructionType::MovePostion);
			instr.fromPosition = std::stoi(parts[2]);
			instr.toPosition = std::stoi(parts[5]);
			return instr;
		}
		if (parts[0] == "rotate" && parts[1] == "based") {
			Instruction instr(InstructionType::RotatePosition);
			instr.fromLetter = parts[6].front();
			return instr;
		}

		throw std::runtime_error("Cant handle input");
	}

	void applySwapPosition(const Instruction& _instruction, std::string& _input) {
		assert(_instruction.type == InstructionType::SwapPosition);

		char cache = _input[_instruction.toPosition];
		_input[_instruction.toPosition] = _input[_instruction.fromPosition];
		_input[_instruction.fromPosition] = cache;
	}

	void applySwapLetter(const Instruction& _instruction, std::string& _input) {
		assert(_instruction.type == InstructionType::SwapLetter);

		std::replace(_input.begin(), _input.end(), _instruction.toLetter, '?');
		std::replace(_input.begin(), _input.end(), _instruction.fromLetter, _instruction.toLetter);
		std::replace(_input.begin(), _input.end(), '?', _instruction.fromLetter);
	}

	void applyReversePositions(const Instruction& _instruction, std::string& _input) {
		assert(_instruction.type == InstructionType::ReversePositions);

		const int size = _instruction.toPosition - _instruction.fromPosition + 1;

		std::reverse(_input.begin() + _instruction.fromPosition, _input.begin() + _instruction.fromPosition + size);
	}

	void applyRotate(const Instruction& _instruction, std::string& _input) {
		assert(_instruction.type == InstructionType::Rotate);

		if (_instruction.steps < 0) {
			std::rotate(_input.begin(), _input.begin() + std::abs(_instruction.steps) % _input.size(), _input.end());
		}
		else {
			std::rotate(_input.rbegin(), _input.rbegin() + std::abs(_instruction.steps) % _input.size(), _input.rend());
		}
	}

	void applyMovePostion(const Instruction& _instruction, std::string& _input) {
		assert(_instruction.type == InstructionType::MovePostion);

		const char val = _input[_instruction.fromPosition];

		_input.erase(_input.begin() + _instruction.fromPosition);
		_input.insert(_input.begin() + _instruction.toPosition, val);
	}

	void applyRotatePosition(const Instruction& _instruction, std::string& _input) {
		assert(_instruction.type == InstructionType::RotatePosition);

		auto index = (int)_input.find(_instruction.fromLetter, 0);

		auto newInstr = Instruction(InstructionType::Rotate);
		newInstr.steps = 1 + index + (index >= 4 ? 1 : 0);
		applyRotate(newInstr, _input);
	}
	
	std::string Day21Puzzle::apply(const Instruction& _instruction, const std::string& _input) {
		auto result(_input);

		switch (_instruction.type) {
		case InstructionType::SwapPosition:
			applySwapPosition(_instruction, result);
			break;
		case InstructionType::SwapLetter:
			applySwapLetter(_instruction, result);
			break;
		case InstructionType::ReversePositions:
			applyReversePositions(_instruction, result);
			break;
		case InstructionType::Rotate:
			applyRotate(_instruction, result);
			break;
		case InstructionType::MovePostion:
			applyMovePostion(_instruction, result);
			break;
		case InstructionType::RotatePosition:
			applyRotatePosition(_instruction, result);
			break;
		}

		return result;
	}
}
