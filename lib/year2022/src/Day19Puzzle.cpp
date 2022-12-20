#include <2022/Day19Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <cassert>
#include <Core/States.hpp>
#include <sstream>
#include <deque>
#include <unordered_map>
#include <unordered_set>
#include <array>

namespace std
{
	template<typename T, size_t N>
	struct hash<array<T, N> >
	{
		typedef array<T, N> argument_type;
		typedef size_t result_type;

		result_type operator()(const argument_type& a) const
		{
			hash<T> hasher;
			result_type h = 0;
			for (result_type i = 0; i < N; ++i)
			{
				h = h * 31 + hasher(a[i]);
			}
			return h;
		}
	};
}

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

	void clampMaxResource(int& _resource, int _resourceRobot, int _maxResourceCost, int _t)
	{
		if (_resource >= _t * _maxResourceCost - _resourceRobot * (_t - 1))
		{
			_resource = _t * _maxResourceCost - _resourceRobot * (_t - 1);
		}
	}

	int solve(const Blueprint& _blueprint, int _time)
	{

		using State = std::array<int, 9>;

		std::unordered_set<State> seen;
		std::deque<State> queue;
		queue.push_back({ 0, 0, 0, 0, 1, 0, 0, 0, _time });

		int best = 0;

		while (!queue.empty())
		{
			const auto curr = queue.front();
			queue.pop_front();

			auto [ore, clay, obs, geo, oreRobot, clayRobot, obsRobot, geoRobot, t] = curr;

			best = std::max(best, geo);
			if (t == 0)
			{
				continue;
			}

			const auto maxOreCost = std::max(
				std::max(_blueprint.OreRobotOreCost, _blueprint.ClayRobotOreCost), 
				std::max(_blueprint.ObsidianRobotOreCost, _blueprint.GeodeRobotOreCost)
			);

			oreRobot = std::min(maxOreCost, oreRobot);
			clayRobot = std::min(_blueprint.ObsidianRobotClayCost, clayRobot);
			obsRobot = std::min(_blueprint.GeodeRobotObsidianCost, obsRobot);
			clampMaxResource(ore, oreRobot, maxOreCost, t);
			clampMaxResource(clay, clayRobot, _blueprint.ObsidianRobotClayCost, t);
			clampMaxResource(obs, obsRobot, _blueprint.GeodeRobotObsidianCost, t);

			State next{ ore, clay, obs, geo, oreRobot, clayRobot, obsRobot, geoRobot, t };

			if (!seen.contains(next))
			{
				seen.insert(next);

				queue.push_back(State{ ore + oreRobot, clay + clayRobot, obs + obsRobot, geo + geoRobot, oreRobot, clayRobot, obsRobot, geoRobot, t - 1 });

				if (ore >= _blueprint.OreRobotOreCost)
				{
					queue.push_back(State{ ore - _blueprint.OreRobotOreCost + oreRobot, clay + clayRobot, obs + obsRobot, geo + geoRobot, oreRobot + 1, clayRobot, obsRobot, geoRobot, t - 1 });
				}
				if (ore >= _blueprint.ClayRobotOreCost)
				{
					queue.push_back(State{ ore - _blueprint.ClayRobotOreCost + oreRobot, clay + clayRobot, obs + obsRobot, geo + geoRobot, oreRobot, clayRobot + 1, obsRobot, geoRobot, t - 1 });
				}
				if (ore >= _blueprint.ObsidianRobotOreCost && clay >= _blueprint.ObsidianRobotClayCost)
				{
					queue.push_back(State{ ore - _blueprint.ObsidianRobotOreCost + oreRobot, clay - _blueprint.ObsidianRobotClayCost + clayRobot, obs + obsRobot, geo + geoRobot, oreRobot, clayRobot, obsRobot + 1, geoRobot, t - 1 });
				}
				if (ore >= _blueprint.GeodeRobotOreCost && obs >= _blueprint.GeodeRobotObsidianCost)
				{
					queue.push_back(State{ ore - _blueprint.GeodeRobotOreCost + oreRobot, clay + clayRobot, obs - _blueprint.GeodeRobotObsidianCost + obsRobot, geo + geoRobot, oreRobot, clayRobot, obsRobot, geoRobot + 1, t - 1 });
				}
			}
		}

		return best;
	}

	std::pair<std::string, std::string> Day19Puzzle::fastSolve() {

		std::vector<Blueprint> blueprints;

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

		int part1 = 0;

		for (const auto& b : blueprints)
		{
			const int qualityLevel = solve(b, 24);
			part1 += qualityLevel * b.id;
		}

		int part2 = 1;
		for (std::size_t i = 0; i < std::min((std::size_t)3, blueprints.size()); ++i)
		{
			const int geodes = solve(blueprints[i], 32);
			part2 *= geodes;
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
