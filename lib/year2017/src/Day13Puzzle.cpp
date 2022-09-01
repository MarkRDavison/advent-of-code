#include <2017/Day13Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <unordered_map>

namespace TwentySeventeen {
	
	Day13Puzzle::Day13Puzzle() :
		core::PuzzleBase("Packet Scanners", 2017, 13) {

	}
	Day13Puzzle::~Day13Puzzle() {

	}


	void Day13Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day13Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day13Puzzle::fastSolve() {

		std::unordered_map<std::size_t, std::size_t> firewall;
		for (const auto& l : m_InputLines) {
			const auto& p = ze::StringExtensions::splitStringByDelimeter(l, " :");
			firewall[(std::size_t)std::stoul(p[0])] = (std::size_t)std::stoul(p[1]);
		}

		std::size_t severity = 0;

		for (const auto& [layer, depth] : firewall) {
			if (layer % ((depth - 1) * 2) == 0) {
				severity += layer * depth;
			}
		}

		std::size_t delay;
		for (delay = 0; ; ++delay) {
			bool valid = true;
			for (const auto& [layer, depth] : firewall) {
				if ((layer + delay) % ((depth - 1) * 2) == 0) {
					valid = false;
					break;
				}
			}
			if (valid) {
				break;
			}
		}

		return { std::to_string(severity), std::to_string(delay) };
	}
}
