#include <2018/Day04Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_map>
#include <algorithm>

namespace TwentyEighteen {

	struct hash_pair {
		template <class T1, class T2>
		size_t operator()(const std::pair<T1, T2>& p) const
		{
			auto hash1 = std::hash<T1>{}(p.first);
			auto hash2 = std::hash<T2>{}(p.second);

			if (hash1 != hash2) {
				return hash1 ^ hash2;
			}

			// If hash1 == hash2, their XOR is zero.
			return hash1;
		}
	};

	Day04Puzzle::Day04Puzzle() :
		core::PuzzleBase("Repose Record", 2018, 4) {

	}
	Day04Puzzle::~Day04Puzzle() {

	}


	void Day04Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day04Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct Shift
	{
		int guardId;
		int month;
		int day;
		std::vector<std::pair<int, int>> asleepRanges;
	};

	std::string zeroPrefix(int _val)
	{
		if (_val < 10)
		{
			return "0" + std::to_string(_val);
		}
		return std::to_string(_val);
	}

	std::pair<std::string, std::string> Day04Puzzle::fastSolve() {
		int part1 = 0;
		int part2 = 0;
		std::vector<Shift> shiftInfo;
		std::sort(m_InputLines.begin(), m_InputLines.end());
		for (const auto& i : m_InputLines)
		{
			const auto& parts = StringExtensions::splitStringByDelimeter(i, "[-: #");
			auto hour = std::stoi(parts[3]);
			auto min = std::stoi(parts[4]);
			auto day = std::stoi(parts[2]);
			if (hour > 0)
			{
				hour = 0;
				min = 0;
				day++;
			}

			if (parts[5] == "Guard")
			{
				if (!shiftInfo.empty()) 
				{
					auto& previousShift = shiftInfo.back();
					std::sort(
						previousShift.asleepRanges.begin(), previousShift.asleepRanges.end(),
						[](const auto& _lhs, const auto& _rhs) -> bool
						{
							return _lhs.first < _rhs.second;
						});
				}
				auto& shift = shiftInfo.emplace_back();
				shift.guardId = std::stoi(parts[6]);
				shift.month = std::stoi(parts[1]);
				shift.day = day;
			}
			else if (parts[5] == "falls")
			{
				auto& shift = shiftInfo.back();
				auto& range = shift.asleepRanges.emplace_back();
				range.first = min;
			}
			else if (parts[5] == "wakes")
			{
				auto& shift = shiftInfo.back();
				auto& range = shift.asleepRanges.back();
				range.second = min;
			}
			else
			{
				throw std::runtime_error("Unexpected input");
			}
		}

		std::sort(
			shiftInfo.begin(), shiftInfo.end(),
			[](const Shift& _lhs, const Shift& _rhs) -> bool
			{
				if (_lhs.month != _rhs.month)
				{
					return _lhs.month < _rhs.month;
				}
				return _lhs.day < _rhs.day;
			});

		if (getVerbose())
		{
			std::cout << "Date   ID   Minute" << std::endl;
			std::cout << "            000000000011111111112222222222333333333344444444445555555555" << std::endl;
			std::cout << "            012345678901234567890123456789012345678901234567890123456789" << std::endl;

			for (const auto& shift : shiftInfo)
			{
				std::cout
					<< zeroPrefix(shift.month) << "-" << zeroPrefix(shift.day) << "  "
					<< "#" << zeroPrefix(shift.guardId) << "  ";

				std::string shiftString(60, '.');

				for (const auto& range : shift.asleepRanges)
				{
					for (int i = range.first; i < range.second; ++i)
					{
						shiftString[(std::size_t)i] = '#';
					}
				}

				std::cout << shiftString << std::endl;
			}
		}

		{	// Part1
			std::unordered_map<int, int> guardAsleepTimes;

			for (const auto& shift : shiftInfo)
			{
				int total = 0;
				for (const auto& range : shift.asleepRanges)
				{
					total += (range.second - range.first);
				}

				guardAsleepTimes[shift.guardId] += total;
			}

			const auto& mostAsleepGuardInfo = *std::max_element(
				guardAsleepTimes.begin(), guardAsleepTimes.end(),
				[](const auto& _lhs, const auto& _rhs) -> bool
				{
					return _lhs.second < _rhs.second;
				});

			std::unordered_map<int, int> guardAsleepMinutes;
			for (const auto& shift : shiftInfo)
			{
				if (shift.guardId != mostAsleepGuardInfo.first)
				{
					continue;
				}


				for (const auto& range : shift.asleepRanges)
				{
					for (int i = range.first; i < range.second; ++i)
					{
						guardAsleepMinutes[i]++;
					}
				}
			}

			const auto& mostAsleepGuardMinuteInfo = *std::max_element(
				guardAsleepMinutes.begin(), guardAsleepMinutes.end(),
				[](const auto& _lhs, const auto& _rhs) -> bool
				{
					return _lhs.second < _rhs.second;
				});

			auto part1Minute = mostAsleepGuardMinuteInfo.first;
			part1 = mostAsleepGuardInfo.first * part1Minute;
		}

		{	//	Part2

			std::unordered_map<std::pair<int, int>, int, hash_pair> guardMinuteAsleepMap;

			for (const auto& shift : shiftInfo)
			{
				int total = 0;
				for (const auto& range : shift.asleepRanges)
				{
					for (int i = range.first; i < range.second; ++i)
					{
						guardMinuteAsleepMap[std::pair<int, int>(shift.guardId, i)] += 1;
					}
				}
			}

			const auto& mostAsleepMinuteInfo = *std::max_element(
				guardMinuteAsleepMap.begin(), guardMinuteAsleepMap.end(),
				[](const auto& _lhs, const auto& _rhs) -> bool
				{
					return _lhs.second < _rhs.second;
				});

			part2 = mostAsleepMinuteInfo.first.first * mostAsleepMinuteInfo.first.second;
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
