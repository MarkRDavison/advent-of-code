#include <2022/Day13Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <unordered_set>
#include <algorithm>
#include <sstream>
#include <cassert>

namespace TwentyTwentyTwo {

	Day13Puzzle::Day13Puzzle() :
		core::PuzzleBase("Distress Signal", 2022, 13) {
	}


	void Day13Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByLines(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0])));
	}

	void Day13Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::vector<std::string> parse(const std::string& _packetString)
	{
		std::vector<std::string> p;
		std::string current;
		std::size_t i = 1;
		while (i < _packetString.size())
		{
			if (i == _packetString.size() - 1) {
				if (!current.empty())
				{
					p.push_back(current);
					current.clear();
				}
				break;
			}
			if (_packetString[i] == '[')
			{
				current += '[';
				int open = 1;
				i++;
				while (true)
				{
					switch (_packetString[i])
					{
					case '[':
						open++;
						break;
					case ']':
						open--;
						break;
					}
					current += _packetString[i];
					if (open == 0)
					{
						break;
					}
					i++;
				}
				p.push_back(current);
				current.clear();
				i++;
				continue;
			}
			if (_packetString[i] == ',')
			{
				if (!current.empty())
				{
					p.push_back(current);
					current.clear();
				}
				i++;
				continue;
			}
			current += _packetString[i];
			i++;
		}

		return p;
	}

	int extractStartingNumber(const std::string& _str)
	{
		const auto end = _str.find_first_not_of("0123456789");
		if (end == 0)
		{
			return -1;
		}
		return std::stoi(_str.substr(0, end));
	}

	int matchVector(std::vector<std::string> _lhs, std::vector<std::string> _rhs)
	{
		for (int i = 0; i < _lhs.size(); ++i)
		{
			if (i >= _rhs.size())
			{
				return 1;
			}

			auto lhsStr = _lhs[i];
			auto rhsStr = _rhs[i];

			std::stringstream lhsStream(lhsStr);
			std::stringstream rhsStream(rhsStr);

			int n1 = extractStartingNumber(lhsStr);
			int n2 = extractStartingNumber(rhsStr);
			if (n1!= -1 && n2 != -1) {
				if (n1 < n2)
					return -1;
				if (n1 > n2)
					return 1;
			}
			else
			{
				if (lhsStr[0] != '[')
				{
					lhsStr = '[' + lhsStr + ']';
				}
				if (rhsStr[0] != '[')
				{
					rhsStr = '[' + rhsStr + ']';
				}
				int val = matchVector(parse(lhsStr), parse(rhsStr));
				if (val != 0) {
					return val;
				}
			}
		}
		return _lhs.size() < _rhs.size() ? -1 : 0;
	}

	int match(std::string _lhs, std::string _rhs)
	{
		if (_lhs[0] != '[')
		{
			_lhs = '[' + _lhs + ']';
		}
		if (_rhs[0] != '[')
		{
			_rhs = '[' + _rhs + ']';
		}

		return matchVector(parse({ _lhs }), parse({ _rhs }));
	}

	std::pair<std::string, std::string> Day13Puzzle::fastSolve() {

		const std::string DividerPacket1 = "[[2]]";
		const std::string DividerPacket2 = "[[6]]";

		std::size_t pairIndex = 1;
		std::size_t part1 = 0;
		std::vector<std::string> allpackets;
		for (std::size_t i = 0; i < m_InputLines.size(); i += 3)
		{
			const auto& str1 = m_InputLines[i + 0];
			const auto& str2 = m_InputLines[i + 1];

			allpackets.push_back(str1);
			allpackets.push_back(str2);
	
			part1 += pairIndex * (match(str1, str2) == -1);

			pairIndex++;
		}

		allpackets.push_back(DividerPacket1);
		allpackets.push_back(DividerPacket2);

		std::sort(allpackets.begin(), allpackets.end(), 
			[](const auto& _lhs, const auto& _rhs) -> bool {
				return match(_lhs, _rhs) == -1;
			});

		int index1 = 0;
		int index2 = 0;

		for (int i = 0; i < allpackets.size(); ++i)
		{
			if (allpackets[i] == DividerPacket1)
			{
				index1 = i + 1;
			}
			if (allpackets[i] == DividerPacket2)
			{
				index2 = i + 1;
			}
		}

		return { std::to_string(part1) , std::to_string(index1 * index2) };
	}
}
