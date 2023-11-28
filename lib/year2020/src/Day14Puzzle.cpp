#include <2020/Day14Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <algorithm>
#include <bitset>
#include <cassert>
#include <set>
#include <functional>

namespace TwentyTwenty {
	
	Day14Puzzle::Day14Puzzle() :
		core::PuzzleBase("Docking Data", 2020, 14) {
	}


	void Day14Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day14Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day14Puzzle::fastSolve() {
		const auto& parsed = parse(m_InputLines);

		const auto part1 = doPart1(parsed);
		const auto part2 = doPart2(parsed);

		return { part1, part2 };
	}

	std::vector<Day14Struct> Day14Puzzle::parse(const std::vector<std::string>& _inputLines) {
		std::vector<Day14Struct> parsed;

		for (unsigned i = 0; i < _inputLines.size(); ++i) {
			const auto& s = StringExtensions::splitStringByDelimeter(_inputLines[i], " []");
			if (s[0] == "mask") {
				auto& current = parsed.emplace_back();
				current.mask = s[2];
			}
			else {
				auto& current = parsed.back();
				current.mem.emplace_back(std::stoll(s[1]),std::stoll(s[3]));
			}
		}

		return parsed;
	}

	std::string Day14Puzzle::doPart1(const std::vector<Day14Struct>& _parsed) {

		std::unordered_map<Day14Number, Day14Number> memory;

		for (const auto& _program : _parsed) {
			assert(_program.mask.size() == 36);
			for (const auto& [loc, val] : _program.mem) {
				const Day14Number memoryValue = val;
				std::bitset<36> value(memoryValue);
				for (unsigned i = 0; i < 36; ++i) {
					if (_program.mask[i] == '0') {
						value[36 - 1 - i] = 0;
					}
					else if (_program.mask[i] == '1') {
						value[36 - 1 - i] = 1;
					}
				}
				const Day14Number maskedValue = value.to_ullong();
				memory[loc] = maskedValue;
			}
		}

		Day14Number sum = 0;
		for (const auto& [loc, val] : memory) {
			sum += val;
		}

		return std::to_string(sum);
	}
	template<typename T>
	void iterateCombinations2(const T& c, Day14Number k, std::function<void(const T&)> _callback) {
		int n = c.size();
		int combo = (1 << k) - 1;
		while (combo < 1 << n) {

			T temp;
			for (int i = 0; i < n; ++i) {
				if ((combo >> i) & 1) {
					temp.push_back(c[i]);
				}
			}
			_callback(temp);

			int x = combo & -combo;
			int y = combo + x;
			int z = (combo & ~y);
			combo = z / x;
			combo >>= 1;
			combo |= y;
		}
	}
	std::string Day14Puzzle::doPart2(const std::vector<Day14Struct>& _parsed) {
		std::unordered_map<Day14Number, Day14Number> memory;

		for (const auto& _program : _parsed) {
			assert(_program.mask.size() == 36);
			for (const auto& [loc, val] : _program.mem) {
				const Day14Number valueValue = val;
				std::bitset<36> location(loc);
				std::vector<Day14Number> floatingBitIndex;
				for (unsigned i = 0; i < 36; ++i) {
					if (_program.mask[i] == '1') {
						location[36 - 1 - i] = 1;
					}
					else if (_program.mask[i] == 'X') {
						location[36 - 1 - i] = 0;
						floatingBitIndex.push_back(36 - 1 - i);
					}
				}

				const auto& call = std::function<void(const std::vector<Day14Number>&)>(
					[&](const std::vector<Day14Number>& _vec) -> void {
						std::bitset<36> floatingLocation(location);
						for (const auto v : _vec) {
							floatingLocation[static_cast<unsigned>(v)] = 1;
						}
						memory[floatingLocation.to_ullong()] = valueValue;
					});

				for (unsigned i = 1; i <= floatingBitIndex.size(); ++i) {
					iterateCombinations2(floatingBitIndex, (Day14Number)i, call);
				}
				call({});
			}
		}

		Day14Number sum = 0;
		for (const auto& [loc, val] : memory) {
			sum += val;
		}

		return std::to_string(sum);
	}
}
