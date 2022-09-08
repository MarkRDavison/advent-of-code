#include <2017/Day24Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <algorithm>
#include <ranges>
#include <cassert>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

namespace TwentySeventeen {

	
	Day24Puzzle::Day24Puzzle() :
		core::PuzzleBase("Electromagnetic Moat", 2017, 24) {

	}
	Day24Puzzle::~Day24Puzzle() {

	}


	void Day24Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day24Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct BridgeComponent {
		int a{ 0 };
		int b{ 0 };
				
		bool consumed{ false };

		void use() { consumed = true; }
		void unuse() { consumed = false; }
	};

	struct Stats {
		int maxStrength{ 0 };
		int maxLength{ 0 };
		int maxLengthMaxStrength{ 0 };
	};

	static void recurser(int _startingValue, std::vector<BridgeComponent>& _components, int _length, int _strength, Stats& _stats) {

		_stats.maxStrength = std::max(_stats.maxStrength, _strength);
		if (_length >= _stats.maxLength) {
			_stats.maxLength = _length;
			_stats.maxLengthMaxStrength = std::max(_stats.maxLengthMaxStrength, _strength);
		}


		for (auto& comp : _components) {
			if (comp.consumed) { continue; }
			if (comp.a == _startingValue || comp.b == _startingValue) {
				comp.use();

				const auto nextStart = comp.a == _startingValue ? comp.b : comp.a;

				recurser(nextStart, _components,  _length + 1, _strength + comp.a + comp.b, _stats);

				comp.unuse();
			}
		}
	}

	std::pair<std::string, std::string> Day24Puzzle::fastSolve() {		
		std::vector<BridgeComponent> bridgeComponents;
		
		std::ranges::for_each(
			m_InputLines | 
			std::views::transform([](const std::string& _line) -> std::vector<std::string> {
				return ze::StringExtensions::splitStringByDelimeter(_line, "/");
			}),
			[&bridgeComponents](const std::vector<std::string>& _sections) -> void {
				auto& comp = bridgeComponents.emplace_back();
				comp.a = std::stoi(_sections[0]);
				comp.b = std::stoi(_sections[1]);
			});

		Stats stats{};

		recurser(0, bridgeComponents, 0, 0, stats);

		return { std::to_string(stats.maxStrength), std::to_string(stats.maxLengthMaxStrength) };
	}
}
