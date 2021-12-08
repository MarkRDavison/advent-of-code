#include <2021/Day08Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <cassert>
#include <set>
#include <algorithm>
#include <iterator>

namespace TwentyTwentyOne {

	const SegmentData Day08Puzzle::DisplaySegmentData = {
		{ 0, { 'a', 'b', 'c', 'e', 'f', 'g' } },
		{ 1, { 'c', 'f' } },
		{ 2, { 'a', 'c', 'd', 'e', 'g' } },
		{ 3, { 'a', 'c', 'd', 'f', 'g' } },
		{ 4, { 'b', 'c', 'd', 'f' } },
		{ 5, { 'a', 'b', 'd', 'f', 'g' } },
		{ 6, { 'a', 'b', 'd', 'e', 'f', 'g' } },
		{ 7, { 'a', 'c', 'f' } },
		{ 8, { 'a', 'b', 'c', 'd', 'e', 'f', 'g' } },
		{ 9, { 'a', 'b', 'c', 'd', 'f', 'g' } },
	};
	const std::unordered_map<int, int> Unique = {
		{ 2, 1 }, // 1 is made of 2
		{ 4, 4 }, // 4 is made of 4
		{ 3, 7 }, // 7 is made of 3
		{ 7, 8 }, // 8 is made of 9
	};

	Day08Puzzle::Day08Puzzle() :
		core::PuzzleBase("Seven Segment Search", 2021, 8) {
	}


	void Day08Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day08Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	long getNumber(char _a, char _b, char _c, char _d, char _e, char _f, char _g, const std::string& _output) {

		const std::unordered_map<char, char> mappings = {
			{_a, 'a'},
			{_b, 'b'},
			{_c, 'c'},
			{_d, 'd'},
			{_e, 'e'},
			{_f, 'f'},
			{_g, 'g'},
		};


		for (const auto& [number, segments] : Day08Puzzle::DisplaySegmentData) {
			bool valid = true;
			if (_output.size() != segments.size()) { continue; }
			for (const auto& c : _output) {
				if (segments.count(mappings.at(c)) == 0) {
					valid = false;
					break;
				}
			}
			if (valid) {
				return (long)number;
			}
		}

		throw std::runtime_error("Error");
	}

	char getA(const std::set<char>& _signals1, const std::set<char>& _signals7) {
		for (const auto s7 : _signals7) {
			if (_signals1.count(s7) == 0) {
				return s7;
			}
		}

		throw std::runtime_error("Error");
	}

	char getG(char _a, const std::set<char>& _signals3, const std::set<char>& _signals4) {
		for (const auto c3 : _signals3) {
			if (c3 == _a) { continue; }
			if (_signals4.count(c3) == 0) {
				return c3;
			}
		}

		throw std::runtime_error("Error");
	}

	char getB(char _d, const std::set<char>& _signals1, const std::set<char>& _signals4) {
		for (const auto c4 : _signals4) {
			if (c4 == _d) { continue; }
			if (_signals1.count(c4) == 0) {
				return c4;
			}
		}

		throw std::runtime_error("Error");
	}

	char getF(char _c, const std::set<char>& _signals1) {
		for (const auto c1 : _signals1) {
			if (c1 == _c) { continue; }
			return c1;
		}

		throw std::runtime_error("Error");
	}

	std::pair<char, char> GetCandE(char _a, char _d, char _g, const std::set<char>& _signals1, const std::set<char>& _signals2) {
		char c;
		char e;

		for (const auto c2 : _signals2) {
			if (c2 == _a || c2 == _d || c2 == _g) { continue; }

			if (_signals1.count(c2) == 0) {
				e = c2;
			}
			else {
				c = c2;
			}
		}

		return { c, e };
	}

	char getD(char _a, char _g, const std::set<char>& _signals1, const std::set<char>& _signals3) {
		for (const auto c3 : _signals3) {
			if (c3 == _a || c3 == _g) { continue; }
			if (_signals1.count(c3) == 0) {
				return c3;
			}
		}

		throw std::runtime_error("Error");
	}

	std::set<char> getSignals2or5(char _desired, char _b, const std::set<char>&_signals25_a, const std::set<char>& _signals25_b) {

		for (const auto c2 : _signals25_a) {
			if (c2 == _b) {
				if (_desired == '2') {
					return _signals25_b;
				}
				else {
					return _signals25_a;
				}
			}
		}
		if (_desired == '2') {
			return _signals25_a;
		} else {
			return _signals25_b;
		}
	}

	std::pair<std::set<char>, int> getSignals3(const std::set<char>& _signals235_a, const std::set<char>& _signals235_b, const std::set<char>& _signals235_c, const std::set<char>& _signals1) {
		int counta = 0;
		int countb = 0;
		int countc = 0;
		for (const char c1 : _signals1) {
			if (_signals235_a.count(c1) != 0) {
				counta++;
			}
			if (_signals235_b.count(c1) != 0) {
				countb++;
			}
			if (_signals235_c.count(c1) != 0) {
				countc++;
			}
		}

		if (counta == 2) {
			return { _signals235_a, 0 };
		}
		if (countb == 2) {
			return { _signals235_b, 1 };
		}
		return { _signals235_c, 2 };
	}

	std::pair<std::string, std::string> Day08Puzzle::fastSolve() {
		const auto& parsed = parseInput(m_InputLines);

		int part1 = 0;

		for (const auto& i : parsed) {
			for (unsigned j = 0; j < 4; ++j) {
				const auto size = i.output[j].size();
				if (Unique.count((int)size) > 0) {
					part1++;
				}
			}
		}

		long part2 = 0;

		const auto addToSet = [](std::set<char>& _set, const std::string& _string) -> void {
			for (const char c : _string) {
				_set.insert(c);
			}
		};

		{
			for (const auto& i : parsed) {
				std::set<char> signals1;
				std::set<char> signals7;
				std::set<char> signals4;
				std::set<char> signals8;
				std::set<char> signals235[3];
				unsigned index235 = 0;
				for (unsigned j = 0; j < 10; ++j) {
					if (i.signals[j].size() == 2) {
						addToSet(signals1, i.signals[j]);
					}
					if (i.signals[j].size() == 3) {
						addToSet(signals7, i.signals[j]);
					}
					if (i.signals[j].size() == 5) {
						addToSet(signals235[index235], i.signals[j]);
						index235++;
					}
					if (i.signals[j].size() == 4) {
						addToSet(signals4, i.signals[j]);
					}
					if (i.signals[j].size() == 7) {
						addToSet(signals8, i.signals[j]);
					}
				}

				char a = getA(signals1, signals7);
				assert(a != '?');

				auto [signals3, signals3Index] = getSignals3(signals235[0], signals235[1], signals235[2], signals1);


				std::vector<std::set<char>> signals25;
				for (unsigned i = 0; i < 3; ++i) {
					if (i != signals3Index) {
						signals25.push_back(signals235[i]);
					}
				}

				char g = getG(a, signals3, signals4);
				char d = getD(a, g, signals1, signals3);
				char b = getB(d, signals1, signals4);

				auto signals2 = getSignals2or5('2', b, signals25[0], signals25[1]);
				auto signals5 = getSignals2or5('5', b, signals25[0], signals25[1]);

				auto [c, e] = GetCandE(a, d, g, signals1, signals2);

				char f = getF(c, signals1);

				if (getVerbose()) {
					std::cout << "_" << a << a << a << a << std::endl;
					std::cout << b << "    " << c << std::endl;
					std::cout << b << "    " << c << std::endl;
					std::cout << " " << d << d << d << d << std::endl;
					std::cout << e << "    " << f << std::endl;
					std::cout << e << "    " << f << std::endl;
					std::cout << " " << g << g << g << g << std::endl;
				}

				long total = 0;
				long multiplier = 1000;
				for (unsigned j = 0; j < 4; ++j) {
					const auto num = getNumber(a, b, c, d, e, f, g, i.output[j]);
					total += num * multiplier;
					multiplier /= 10;
				}

				std::cout << total << std::endl;

				part2 += total;
			}
		}



		return { std::to_string(part1), std::to_string(part2) };
	}

	std::vector<SegmentInput> Day08Puzzle::parseInput(const std::vector<std::string>& _inputLines) {
		std::vector<SegmentInput> parsed;

		for (const auto& i : _inputLines) {
			const auto& parts = ze::StringExtensions::splitStringByDelimeter(i, "|");
			const auto& segments = ze::StringExtensions::splitStringByDelimeter(parts[0], " ");
			const auto& output = ze::StringExtensions::splitStringByDelimeter(parts[1], " ");

			assert(segments.size() == 10);
			assert(output.size() == 4);

			auto& current = parsed.emplace_back();
			for (unsigned j = 0; j < 4; ++j) {
				current.output[j] = output[j];
			}

			bool found2 = false;
			bool found3 = false;
			bool found4 = false;


			for (unsigned j = 0; j < 10; ++j) {
				current.signals[j] = segments[j];

				if (segments[j].size() == 2) {
					found2 = true;
				}
				if (segments[j].size() == 3) {
					found3 = true;
				}
				if (segments[j].size() == 4) {
					found4 = true;
				}
			}

			assert(found2 && found3 && found4);
		}

		return parsed;
	}
}
