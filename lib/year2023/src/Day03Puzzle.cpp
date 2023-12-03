#include <2023/Day03Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <unordered_map>
#include <unordered_set>

namespace TwentyTwentyThree {
	
	Day03Puzzle::Day03Puzzle() :
		core::PuzzleBase("Gear Ratios", 2023, 3) {
	}


	void Day03Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day03Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct SchematicNumber
	{
		bool adj{ false };
		int number{ 0 };
	};

	struct SchematicCell
	{
		char c{'.'};
		int number;
		bool adjacentSymbol;
		SchematicNumber* sn{ nullptr };

		bool isMagicSymbol()
		{
			auto res = c != '.' && c != '0' && c != '1' && c != '2' && c != '3' && c != '4' && c != '5' && c != '6' && c != '7' && c != '8' && c != '9';
			return res;
		}
	};

	std::pair<std::string, std::string> Day03Puzzle::fastSolve() {

		core::Region<SchematicCell> schematic;

		std::vector< SchematicNumber*> sns;

		std::vector<std::unordered_set<SchematicNumber*>> gearNumbers;

		for (int y = 0; y < m_InputLines.size(); ++y)
		{
			int currentNumber = -1;
			SchematicNumber* currsn{ nullptr };
			for (int x = 0; x < m_InputLines[y].size(); ++x)
			{
				auto& cell = schematic.getCell(x, y);
				cell.c = m_InputLines[y][x];

				if ('0' <= cell.c && cell.c <= '9')
				{
					if (currentNumber == -1)
					{
						auto end = m_InputLines[y].find_first_not_of("0123456789", x);
						auto number = m_InputLines[y].substr(x, end - x);

						currentNumber = std::stoi(number);
						currsn = sns.emplace_back(new SchematicNumber());
						currsn->adj = false;
						currsn->number = currentNumber;
					}
					cell.number = currentNumber;
					cell.sn = currsn;
				}

				if ('.' == cell.c || cell.c > '9' || cell.c < '0')
				{
					if (currentNumber != -1)
					{
						currentNumber = -1;
					}
				}
			}
		}

		for (int y = 0; y < m_InputLines.size(); ++y)
		{
			for (int x= 0; x < m_InputLines[y].size(); ++x)
			{
				auto& cell = schematic.getCell(x, y);
				if (cell.isMagicSymbol())
				{

					bool isGear = cell.c == '*';
					auto& newGearVals =
						gearNumbers.emplace_back();

					int touching = 0;

					for (int yOff = -1; yOff <= +1; ++yOff)
					{
						for (int xOff = -1; xOff <= +1; ++xOff)
						{
							if (xOff == 0 && yOff == 0) { continue; }

							auto& adjcell = schematic.getCell(x + xOff, y + yOff);
							if ('0' <= adjcell.c && adjcell.c <= '9')
							{
								adjcell.adjacentSymbol = true;
								adjcell.sn->adj = true;
								touching++;
								if (isGear)
								{
									newGearVals.emplace(adjcell.sn);
								}
							}
						}
					}
				}
			}
		}

		long long part1 = 0;
		bool startTalking = false;

		for (int y = 0; y < m_InputLines.size(); ++y)
		{
			for (int x = 0; x < m_InputLines[y].size(); ++x)
			{
				auto& cell = schematic.getCell(x, y);
				if (cell.number != -1 && cell.adjacentSymbol)
				{
					part1 += cell.number;

					int off = 0;
					while (true)
					{
						const auto cc = schematic.getCell(x + 1 + off, y).c;
						if (!('0' <= cc && cc <= '9'))
						{
							break;
						}

						off++;
					}

					x += off;
				}
			}
		}

		long long part1b = 0;

		for (const auto& sn : sns)
		{
			if (sn->adj)
			{
				part1b += sn->number;
			}
		}

		long long part2 = 0;

		for (const auto& gv : gearNumbers)
		{
			if (gv.size() == 2)
			{
				long long p2c = 1;
				for (const auto& sn : gv)
				{
					p2c *= sn->number;
				}
				part2 += p2c;
			}
		}

		return { std::to_string(part1), std::to_string(part2)};
	}
}
