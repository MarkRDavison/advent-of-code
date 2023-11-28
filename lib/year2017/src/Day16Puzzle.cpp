#include <2017/Day16Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_map>
#include <unordered_set>

namespace TwentySeventeen {
	
	Day16Puzzle::Day16Puzzle() :
		core::PuzzleBase("Permutation Promenade", 2017, 16) {

	}
	Day16Puzzle::~Day16Puzzle() {

	}


	void Day16Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day16Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	static void spin(std::string& _programs, std::size_t _amount) {
		_programs = _programs.substr(_programs.size() - _amount) + _programs.substr(0, _programs.size() - _amount);
	}

	static void exchange(std::string& _programs, std::size_t _pos1, std::size_t _pos2) {
		std::swap(_programs[_pos1], _programs[_pos2]);
	}

	static void partner(std::string& _programs, char _program1, char _program2) {
		std::swap(_programs[_programs.find(_program1)], _programs[_programs.find(_program2)]);
	}

	std::pair<std::string, std::string> Day16Puzzle::fastSolve() {
		return fastSolve(16);
	}

	struct ParsedInstruction {
		enum Type {
			Spin,
			Partner,
			Exchange
		} type;

		std::size_t num1, num2;
		char char1, char2;
	};

	std::pair<std::string, std::string> Day16Puzzle::fastSolve(std::size_t _size) {

		const auto runPart = [&_size, this](std::size_t _iter) -> std::string {
			std::string programs;
			for (std::size_t i = 0; i < _size; ++i) {
				programs += (char)(i + 'a');
			}

			std::vector<ParsedInstruction> instructions;

			for (const auto& instr : StringExtensions::splitStringByDelimeter(m_InputLines[0], ",")) {
				const auto& parts = StringExtensions::splitStringByDelimeter(instr.substr(1), "/");
				auto& parsed = instructions.emplace_back();
				switch (instr[0]) {
				case 's':
					parsed.type = ParsedInstruction::Spin;
					parsed.num1 = (std::size_t)std::stoul(parts[0]);
					break;
				case 'x':
					parsed.type = ParsedInstruction::Exchange;
					parsed.num1 = (std::size_t)std::stoul(parts[0]);
					parsed.num2 = (std::size_t)std::stoul(parts[1]);
					break;
				case 'p':
					parsed.type = ParsedInstruction::Partner;
					parsed.char1 = parts[0][0];
					parsed.char2 = parts[1][0];
					break;
				}
			}

			std::unordered_map<std::string, std::vector<std::size_t>> occurences;

			std::size_t i = 0;
			while (true && i < _iter) {
				for (const auto& instr : instructions) {
					switch (instr.type) {
					case ParsedInstruction::Spin:
						spin(programs, instr.num1);
						break;
					case ParsedInstruction::Exchange:
						exchange(programs, instr.num1, instr.num2);
						break;
					case ParsedInstruction::Partner:
						partner(programs, instr.char1, instr.char2);
						break;
					}
				}

				if (occurences.count(programs) > 0 && occurences[programs].size() > 2) {
					break;
				}

				occurences[programs].push_back(i);
				i++;
			}

			if (_iter > 1) {
				const auto difference = occurences[programs][1] - occurences[programs][0];

				const auto answer = (_iter % difference) - 1;

				for (const auto& [k, v] : occurences) {
					for (const auto iter : v) {
						if (iter == answer) {
							return k;
						}
					}
				}
			}

			return programs;
		};
		

		return { runPart(1), runPart(1000000000) };
	}
}
