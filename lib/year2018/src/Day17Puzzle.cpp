#include <2018/Day17Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Vector2.hpp>
#include <Core/Pathfinding.hpp>
#include <queue>

#define CLAY '#'
#define SAND ' '
#define SOURCE '+'
#define SETTLED '~'
#define FLOW '|'

#define IS_EMPTY(s) (s == SAND || s == 0)
#define IS_SOLID(s) (s == CLAY || s == SETTLED)
#define IS_CLAY(s) (s == CLAY)

namespace TwentyEighteen {
	
	Day17Puzzle::Day17Puzzle() :
		core::PuzzleBase("Reservoir Research", 2018, 17) {

	}
	Day17Puzzle::~Day17Puzzle() {

	}


	void Day17Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day17Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	void dumpMap(core::Region<Day17Puzzle::ClayCell>& _map, int maxYToDraw, int height) {
		std::cout << "=======================" << std::endl;
		for (int y = maxYToDraw - height; y <= maxYToDraw; ++y) {
			for (int x = _map.minX; x <= _map.maxX; ++x) {
				std::cout << _map.getCell(x, y).c;
			}
			std::cout << std::endl;
		}
	}

	void safelyFlowUp(core::Region<Day17Puzzle::ClayCell>& map, internal::PriorityQueue<Vector2i, int>& locations, int x, int y)
	{
		auto& curr = map.getCell(x, y).c;
		if (curr == FLOW && map.getCell(x, y).c == FLOW)
		{
			locations.put({ x, y - 1 }, y - 1);
		}
	}

	std::pair<std::string, std::string> Day17Puzzle::fastSolve() {
		core::Region<ClayCell> map;

		map.getCell(500, 0).c = SOURCE;
		map.minX = 500;
		map.maxX = 500;
		const auto& parsed = parseInput(m_InputLines);
		populateMap(map, parsed);
		internal::PriorityQueue<Vector2i, int> locations;

		locations.put({ 500, 0 }, 0);

		int displayHeight = 64;
		int currentY = displayHeight;

		int minY = 500;
		for (const auto& p : parsed)
		{
			minY = std::min(minY, p.minY);
		}
		const auto maxY = map.maxY;


		if (getVerbose())
		{
			dumpMap(map, currentY, displayHeight);
		}

		while (!locations.empty()) {

			Vector2i loc = locations.get();

			if (loc.y > maxY + 2) { continue; }

			currentY = std::max(currentY, loc.y + displayHeight / 2);

			auto& below = map.getCell(loc.x, loc.y + 1).c;
			if (IS_EMPTY(below)) {
				locations.put({ loc.x, loc.y + 1 }, loc.y + 1);
				below = FLOW;
			}
			else if (IS_SOLID(below)) {
				bool containedLeft = false;
				bool containedRight = false;
				int minX = loc.x;
				int maxX = loc.x;

				while (true)
				{
					const int leftX = minX - 1;

					const auto belowLeftCoord = Vector2i{ leftX, loc.y + 1 };
					const auto adjLeftCoord = Vector2i{ leftX, loc.y };

					if (IS_SOLID(map.getCell(adjLeftCoord.x, adjLeftCoord.y).c))
					{
						containedLeft = true;
						break;
					}
					else if (IS_SOLID(map.getCell(belowLeftCoord.x, belowLeftCoord.y).c))
					{
						minX--;
					}
					else 
					{
						break;
					}
				}

				while (true)
				{
					const int rightX = maxX + 1;

					const auto belowRightCoord = Vector2i{ rightX, loc.y + 1 };
					const auto adjRightCoord = Vector2i{ rightX, loc.y };

					if (IS_SOLID(map.getCell(adjRightCoord.x, adjRightCoord.y).c))
					{
						containedRight = true;
						break;
					}
					else if (IS_SOLID(map.getCell(belowRightCoord.x, belowRightCoord.y).c))
					{
						maxX++;
					}
					else
					{
						break;
					}
				}
								
				if (containedLeft && containedRight)
				{
					for (int x = minX; x <= maxX; ++x)
					{
						map.getCell(x, loc.y).c = SETTLED;
					}

					locations.put({ loc.x, loc.y - 1 }, loc.y - 1);
				}
				else
				{
					// Flowing water over the top
					for (int x = minX; x <= loc.x; ++x)
					{
						safelyFlowUp(map, locations, x, loc.y);
						map.getCell(x, loc.y).c = FLOW;
					}
					if (!containedLeft)
					{
						safelyFlowUp(map, locations, minX, loc.y);
						safelyFlowUp(map, locations, minX-1, loc.y);
						map.getCell(minX, loc.y).c = FLOW;
						map.getCell(minX - 1, loc.y).c = FLOW;
						locations.put({ minX - 1, loc.y }, loc.y);
					}

					for (int x = loc.x; x <= maxX; ++x)
					{
						safelyFlowUp(map, locations, x, loc.y);
						map.getCell(x, loc.y).c = FLOW;
					}
					if (!containedRight)
					{
						safelyFlowUp(map, locations, maxX, loc.y);
						safelyFlowUp(map, locations, maxX+1, loc.y);
						map.getCell(maxX, loc.y).c = FLOW;
						map.getCell(maxX + 1, loc.y).c = FLOW;
						locations.put({ maxX + 1, loc.y }, loc.y);
					}
				}
			}

			if (getVerbose())
			{
				dumpMap(map, currentY, displayHeight);
			}
		}

		long long part1 = 0;
		long long part2 = 0;

		for (int y = minY; y <= maxY; ++y)
		{
			for (int x = map.minX; x <= map.maxX; ++x)
			{
				const auto& c = map.getCell(x, y).c;
				if (c == SETTLED)
				{
					part1++;
					part2++;
				}
				if (c == FLOW)
				{
					part1++;
				}
			}
		}

		if (getVerbose())
		{
			dumpMap(map, map.maxY, map.maxY);
		}

		return { std::to_string(part1), std::to_string(part2) };
	}

	std::vector<Day17Puzzle::ParsedClayVein> Day17Puzzle::parseInput(const std::vector<std::string>& _input) {
		std::vector<Day17Puzzle::ParsedClayVein> parsed;

		for (const auto& line : _input) {
			const auto& parts = StringExtensions::splitStringByDelimeter(line, "=,.");
			auto c1 = std::stoi(parts[1]);
			auto c2_s = std::stoi(parts[3]);
			auto c2_e = std::stoi(parts[4]);

			auto& pcv = parsed.emplace_back();
			if (parts[0] == "x") {
				pcv.minX = c1;
				pcv.maxX = c1;
				pcv.minY = c2_s;
				pcv.maxY = c2_e;
			}
			else {
				pcv.minY = c1;
				pcv.maxY = c1;
				pcv.minX = c2_s;
				pcv.maxX = c2_e;
			}
		}

		return parsed;
	}
	void Day17Puzzle::populateMap(core::Region<ClayCell>& _map, const std::vector<ParsedClayVein>& _parsedInput) {
		for (const auto& pcv : _parsedInput) {
			for (int y = pcv.minY; y <= pcv.maxY; ++y){
				for (int x = pcv.minX; x <= pcv.maxX; ++x) {
					_map.getCell(x, y).c = CLAY;
				}
			}
		}
	}
}
