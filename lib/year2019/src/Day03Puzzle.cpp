#include <2019/Day03Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Vector2.hpp>
#include <unordered_map>
#include <numeric>

namespace TwentyNineteen {
	
	Day03Puzzle::Day03Puzzle() :
		core::PuzzleBase("Crossed Wires", 2019, 3) {

	}
	Day03Puzzle::~Day03Puzzle() {

	}


	void Day03Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day03Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day03Puzzle::fastSolve() {
		std::unordered_map<Vector2i, bool[2], Vector2_Hash_Fxn<int>> wirePaths;
		std::unordered_map<Vector2i, int[2], Vector2_Hash_Fxn<int>> wireDistances;
		const std::unordered_map<char, Vector2i> dirs = {
			{'R', {+1,0}},
			{'L', {-1,0}},
			{'U', {0,-1}},
			{'D', {0,+1}},
		};

		
		const auto& runWire =
			[&](const std::string& line, std::size_t index) -> void
			{
				Vector2i curr;
				int distance = 0;
				for (const auto& instr : StringExtensions::splitStringByDelimeter(line, ","))
				{
					const auto dir = instr[0];
					const auto length = std::stoi(instr.substr(1));

					for (int i = 0; i < length; ++i)
					{
						distance++;
						curr += dirs.at(dir);
						if (!wirePaths[curr][index])
						{
							wireDistances[curr][index] = distance;
						}
						wirePaths[curr][index] = true;
					}
				}
			};

		runWire(m_InputLines[0], 0);
		runWire(m_InputLines[1], 1);

		int part1 = std::numeric_limits<int>::max();
		int part2 = std::numeric_limits<int>::max();
		for (const auto& [coord, amount] : wirePaths)
		{
			if (amount[0] && amount[1])
			{
				const auto manhatten = std::abs(coord.x) + std::abs(coord.y);
				if (part1 > manhatten)
				{
					part1 = manhatten;
				}
				const auto distance = wireDistances[coord][0] + wireDistances[coord][1];
				if (part2 > distance)
				{
					part2 = distance;
				}
			}
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
