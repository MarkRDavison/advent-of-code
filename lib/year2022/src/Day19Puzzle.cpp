#include <2022/Day19Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <cassert>
#include <Core/States.hpp>
#include <sstream>
#include <queue>
#include <unordered_map>
#include <unordered_set>

namespace TwentyTwentyTwo {
	
	Day19Puzzle::Day19Puzzle() :
		core::PuzzleBase("Not Enough Minerals", 2022, 19) {
	}


	void Day19Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day19Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct Blueprint
	{
		int id{ -1 };
		int OreRobotOreCost{ -1 };
		int ClayRobotOreCost{ -1 };
		int ObsidianRobotOreCost{ -1 };
		int ObsidianRobotClayCost{ -1 };
		int GeodeRobotOreCost{ -1 };
		int GeodeRobotObsidianCost{ -1 };
	};

	struct PointlessStateInfo {
		Blueprint blueprint;
	};

	struct ProcessState {

		ProcessState() {}
		ProcessState(const ProcessState& _other) 
		{
			minute = _other.minute;
			OreRobot = _other.OreRobot;
			ClayRobot = _other.ClayRobot;
			ObsidianRobot = _other.ObsidianRobot;
			GeodeRobot = _other.GeodeRobot;
			Ore = _other.Ore;
			Clay = _other.Clay;
			Obsidian = _other.Obsidian;
			Geode = _other.Geode;
		}

		int minute{ 0 };

		int OreRobot{ 1 };
		int ClayRobot{ 0 };
		int ObsidianRobot{ 0 };
		int GeodeRobot{ 0 };

		int Ore{ 0 };
		int Clay{ 0 };
		int Obsidian{ 0 };
		int Geode{ 0 };

		std::string str() const {
			std::stringstream ss;

			ss << minute << "-";
			ss << OreRobot << "-" << ClayRobot << "-" << ObsidianRobot << "-" << GeodeRobot << "-";
			ss << Ore << "-" << Clay << "-" << Obsidian << "-" << Geode << "-";

			return ss.str();
		}

		bool canAfford(bool _ore, bool _clay, bool _obsidian, bool _geode, const ProcessState& _state, const Blueprint& _blueprint) const
		{
			int oreCost = 0;
			int clayCost = 0;
			int obsidianCost = 0;

			if (_ore)
			{
				oreCost += _blueprint.OreRobotOreCost;
			}
			if (_clay)
			{
				oreCost += _blueprint.ClayRobotOreCost;
			}
			if (_obsidian)
			{
				oreCost += _blueprint.ObsidianRobotOreCost;
				clayCost += _blueprint.ObsidianRobotClayCost;
			}
			if (_geode)
			{
				oreCost += _blueprint.GeodeRobotOreCost;
				obsidianCost += _blueprint.GeodeRobotObsidianCost;
			}

			const auto maxOrePerMinute = _blueprint.OreRobotOreCost + _blueprint.ClayRobotOreCost + _blueprint.ObsidianRobotOreCost + _blueprint.GeodeRobotOreCost;
			if (_state.OreRobot + 1 > maxOrePerMinute)
			{
				return false;
			}
			const auto maxClayPerMinute = _blueprint.ObsidianRobotClayCost;
			if (_state.ClayRobot + 1 > maxClayPerMinute)
			{
				return false;
			}
			const auto maxObsPerMinute = _blueprint.GeodeRobotObsidianCost;
			if (_state.ObsidianRobot +1 > maxClayPerMinute)
			{
				return false;
			}

			return
				oreCost <= _state.Ore &&
				clayCost <= _state.Clay &&
				obsidianCost <= _state.Obsidian;
		}

		ProcessState make(bool _ore, bool _clay, bool _obsidian, bool _geode, const ProcessState& _state, const Blueprint& _blueprint) const
		{
			int oreCost = 0;
			int clayCost = 0;
			int obsidianCost = 0;

			if (_ore)
			{
				oreCost += _blueprint.OreRobotOreCost;
			}
			if (_clay)
			{
				oreCost += _blueprint.ClayRobotOreCost;
			}
			if (_obsidian)
			{
				oreCost += _blueprint.ObsidianRobotOreCost;
				clayCost += _blueprint.ObsidianRobotClayCost;
			}
			if (_geode)
			{
				oreCost += _blueprint.GeodeRobotOreCost;
				obsidianCost += _blueprint.GeodeRobotObsidianCost;
			}

			ProcessState next(_state);
			next.minute++;

			next.Ore -= oreCost;
			assert(next.Ore >= 0);

			next.Clay -= clayCost;
			assert(next.Clay >= 0);

			next.Obsidian -= obsidianCost;
			assert(next.Obsidian >= 0);

			next.Ore += next.OreRobot;
			next.Clay += next.ClayRobot;
			next.Obsidian += next.ObsidianRobot;
			next.Geode += next.GeodeRobot;

			if (_ore)
			{
				next.OreRobot++;
			}
			if (_clay)
			{
				next.ClayRobot++;
			}
			if (_obsidian)
			{
				next.ObsidianRobot++;
			}
			if (_geode)
			{
				next.GeodeRobot++;
			}
			return next;
		}

		std::vector<ProcessState> enumerate(const PointlessStateInfo& _info) const {
			std::vector<ProcessState> available;

			ProcessState next(*this);

			for (int ore = 0; ore <= 1; ++ore)
			{
				for (int clay = 0; clay <= 1; ++clay)
				{
					for (int obs = 0; obs <= 1; ++obs)
					{
						for (int geo = 0; geo <= 1; ++geo)
						{
							if (canAfford(ore == 1, clay == 1, obs == 1, geo == 1, *this, _info.blueprint))
							{
								const auto nextPopulated = make(ore == 1, clay == 1, obs == 1, geo == 1, *this, _info.blueprint);
								if (nextPopulated.minute >= 24)
								{
									continue;
								}
								available.push_back(nextPopulated);
							}
						}
					}
				}
			}

			return available;
		}
	};

	std::pair<std::string, std::string> Day19Puzzle::fastSolve() {

		std::vector<Blueprint> blueprints;

		std::cout << m_InputLines[0] << std::endl;

		for (const auto& l : m_InputLines)
		{
			auto& blueprint = blueprints.emplace_back();

			const auto& p = ze::StringExtensions::splitStringByDelimeter(l, ":.");

			const auto id = std::stoi(ze::StringExtensions::splitStringByDelimeter(p[0], " ")[1]);
			assert(id > 0);

			blueprint.id = id;

			{
				const auto& oreRobotCost = ze::StringExtensions::splitStringByDelimeter(p[1], " ");
				blueprint.OreRobotOreCost = std::stoi(oreRobotCost[4]);
			}
			{
				const auto& clayRobotCost = ze::StringExtensions::splitStringByDelimeter(p[2], " ");
				blueprint.ClayRobotOreCost = std::stoi(clayRobotCost[4]);
			}
			{
				const auto& obsidianRobotCost = ze::StringExtensions::splitStringByDelimeter(p[3], " ");
				blueprint.ObsidianRobotOreCost = std::stoi(obsidianRobotCost[4]);
				blueprint.ObsidianRobotClayCost = std::stoi(obsidianRobotCost[7]);
			}
			{
				const auto& geodeRobotCost = ze::StringExtensions::splitStringByDelimeter(p[4], " ");
				blueprint.GeodeRobotOreCost = std::stoi(geodeRobotCost[4]);
				blueprint.GeodeRobotObsidianCost = std::stoi(geodeRobotCost[7]);
			}
		}

		const int minutes = 24;


		for (const auto& b : blueprints)
		{
			PointlessStateInfo info;
			info.blueprint = b;

			std::queue<ProcessState> queue;
			queue.push(ProcessState());
			std::unordered_set<std::string> seen;

			int maxGeodes = 0;

			int maxOreRobot = 0;
			int maxClayRobot = 0;
			int maxObsRobot = 0;
			int maxGeoRobot = 0;

			while (!queue.empty())
			{
				const auto curr = queue.front();
				queue.pop();

				bool maxMade = false;
				if (maxOreRobot < curr.OreRobot)
				{
					maxMade = true;
					maxOreRobot = curr.OreRobot;
				}
				if (maxClayRobot < curr.ClayRobot)
				{
					maxMade = true;
					maxClayRobot = curr.ClayRobot;
				}
				if (maxObsRobot < curr.ObsidianRobot)
				{
					maxMade = true;
					maxObsRobot = curr.ObsidianRobot;
				}
				if (maxGeoRobot < curr.GeodeRobot)
				{
					maxMade = true;
					maxGeoRobot = curr.GeodeRobot;
				}

				if (maxMade)
				{
					std::cout << "New max robot: " << maxOreRobot << "-" << maxClayRobot << "-" << maxObsRobot << "-" << maxGeoRobot << ", queue: " << queue.size() << ", seen: " << seen.size() << std::endl;
				}

				if (curr.Geode > maxGeodes)
				{
					maxGeodes = curr.Geode;
					std::cout << "New max geodes: " << maxGeodes << std::endl;
				}

				for (const auto& n : curr.enumerate(info))
				{
					const auto hash = n.str();
					if (!seen.contains(hash))
					{
						seen.insert(hash);
						queue.push(n);
					}
				}
			}
			break;
		}


		return { "Part 1", "Part 2" };
	}
}
