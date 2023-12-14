#include <2018/Day24Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_set>
#include <algorithm>
#include <cassert>

namespace TwentyEighteen {
	
	Day24Puzzle::Day24Puzzle() :
		core::PuzzleBase("Immune System Simulator 20XX", 2018, 24) {

	}
	Day24Puzzle::~Day24Puzzle() {

	}

	struct Group
	{		
		int number{ -1 };
		bool active{ true };
		int units{ 0 };
		int hp{ 0 };
		int initiative{ 0 };
		int attack{ 0 };
		std::unordered_set<std::string> weak;
		std::unordered_set<std::string> immune;
		std::string attackType;
		std::string team;

		int targetInitiativeValue{ -1 };
		int targetedByInitiativeValue{ -1 };

		void reset()
		{
			targetInitiativeValue = -1;
			targetedByInitiativeValue = -1;
		}

		int effectivePower() const { return units * attack; }
	};

	void Day24Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day24Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<int, int> solve(bool writeOutput, std::vector<Group> units, int boost)
	{
		for (auto& u : units)
		{
			if (u.team == "Immune")
			{
				u.attack += boost;
			}
		}

		const auto sortTargeting =
			[](std::vector<Group>& u) -> void
			{
				std::sort(u.begin(), u.end(),
					[](const Group& lhs, const Group& rhs) -> bool
					{
						if (lhs.effectivePower() == rhs.effectivePower())
						{
							return lhs.initiative > rhs.initiative;
						}
						return lhs.effectivePower() > rhs.effectivePower();
					});
			};

		const auto sortCombat =
			[](std::vector<Group>& u) -> void
			{
				std::sort(u.begin(), u.end(),
					[](const Group& lhs, const Group& rhs) -> bool
					{
						return lhs.initiative > rhs.initiative;
					});
			};

		const auto startRound =
			[writeOutput](std::vector<Group>& u) -> void
			{
				for (auto& unit : u)
				{
					unit.reset();
				}
				if (writeOutput)
				{
					std::cout << "\n=================================================\n";
					std::cout << "Immune System:\n";
				}
				bool immPresent = false;
				for (auto& unit : u)
				{
					if (unit.team == "Infection")
					{
						continue;
					}
					immPresent = true;

					if (writeOutput)
					{
						std::cout << "Group " << unit.number << " contains " << unit.units << " units\n";
					}
				}
				if (!immPresent && writeOutput)
				{
					std::cout << "No groups remain\n";
				}

				bool infPresent = false;
				if (writeOutput)
				{
					std::cout << "Infection:\n";
				}
				for (auto& unit : u)
				{
					if (unit.team == "Immune")
					{
						continue;
					}
					infPresent = true;
					if (writeOutput)
					{
						std::cout << "Group " << unit.number << " contains " << unit.units << " units\n";
					}
				}
				if (!infPresent && writeOutput)
				{
					std::cout << "No groups remain\n";
				}

				if (writeOutput)
				{
					std::cout << std::endl;
				}
			};

		const auto removeInactive =
			[](std::vector<Group>& u) -> void
			{
				u.erase(std::remove_if(
					u.begin(),
					u.end(),
					[](const Group& g)->bool
					{
						return !g.active;
					}), u.end());
			};

		const auto findTarget =
			[writeOutput](Group& curr, std::vector<Group>& u) -> void
			{
				int currentMaxDamage = 0;
				int currTargetEffectivePower = 0;
				int currTargetInitiative = 0;
				Group* currTarget = nullptr;
				for (auto& t : u)
				{
					if (t.team == curr.team)
					{
						continue;
					}
					if (t.targetedByInitiativeValue != -1)
					{
						continue;
					}

					auto damageDealt = curr.effectivePower();
					if (t.weak.contains(curr.attackType))
					{
						damageDealt *= 2;
					}
					else if (t.immune.contains(curr.attackType))
					{
						damageDealt = 0;
						continue;
					}

					if (writeOutput)
					{
						std::cout << curr.team << " group " << curr.number << " would deal defending group " << t.number << " " << damageDealt << " damage\n";
					}

					if (currentMaxDamage < damageDealt)
					{
						currentMaxDamage = damageDealt;
						currTarget = &t;
						currTargetEffectivePower = t.effectivePower();
						currTargetInitiative = t.initiative;
					}
					else if (
						currentMaxDamage == damageDealt &&
						currTargetEffectivePower < t.effectivePower())
					{
						currentMaxDamage = damageDealt;
						currTarget = &t;
						currTargetEffectivePower = t.effectivePower();
						currTargetInitiative = t.initiative;
					}
					else if (
						currentMaxDamage == damageDealt &&
						currTargetEffectivePower == t.effectivePower() &&
						currTargetInitiative < t.initiative)
					{
						currentMaxDamage = damageDealt;
						currTarget = &t;
						currTargetEffectivePower = t.effectivePower();
						currTargetInitiative = t.initiative;
					}
				}

				if (currTarget != nullptr)
				{
					currTarget->targetedByInitiativeValue = curr.initiative;
					curr.targetInitiativeValue = currTarget->initiative;
				}
			};

		const auto runTargeting =
			[&findTarget, writeOutput](std::vector<Group>& u) -> void
			{
				for (auto& g : u)
				{
					findTarget(g, u);
				}

				if (writeOutput)
				{
					std::cout << std::endl;
				}
			};

		const auto attack =
			[writeOutput](Group& curr, std::vector<Group>& u) -> void
			{
				if (!curr.active) { return; }
				for (auto& target : u)
				{
					if (target.initiative == curr.targetInitiativeValue)
					{
						int damageDealt = curr.effectivePower();
						if (target.weak.contains(curr.attackType)) { damageDealt *= 2; }
						int killed = std::min(damageDealt / target.hp, target.units);
						target.units -= killed;
						if (target.units <= 0)
						{
							target.units = 0;
							target.active = false;
						}
						if (writeOutput)
						{
							std::cout << curr.team << " group " << curr.number << " attacks defending group " << target.number << ", killing " << killed << " units\n";
						}
						return;
					}
				}
			};

		const auto runCombat =
			[&attack, writeOutput](std::vector<Group>& u) -> void
			{
				for (auto& g : u)
				{
					attack(g, u);
				}

				if (writeOutput)
				{
					std::cout << std::endl;
				}
			};

		const auto getRemainingGroups =
			[](const std::vector<Group>& u) -> std::pair<int, int>
			{
				int immuneSystemUnits = 0;
				int infectionUnits = 0;

				for (const Group& g : u)
				{
					if (g.team == "Immune")
					{
						immuneSystemUnits++;
					}
					else
					{
						infectionUnits++;
					}
				}

				return { immuneSystemUnits, infectionUnits };
			};

		const auto getRemainingUnits =
			[](const std::vector<Group>& u) -> std::pair<int, int>
			{
				int immuneSystemUnits = 0;
				int infectionUnits = 0;

				for (const Group& g : u)
				{
					if (g.team == "Immune")
					{
						immuneSystemUnits += g.units;
					}
					else
					{
						infectionUnits += g.units;
					}
				}

				return { immuneSystemUnits, infectionUnits };
			};

		int remainingImmune = 0;
		int remainingInfection = 0;
		while (true)
		{
			startRound(units);

			sortTargeting(units);
			runTargeting(units);

			sortCombat(units);
			runCombat(units);

			removeInactive(units);

			const auto& [imm, inf] = getRemainingGroups(units);
			const auto& [immUnits, infUnits] = getRemainingUnits(units);

			if (remainingImmune == immUnits && remainingInfection == infUnits)
			{
				return { -1,-1 };
			}

			remainingImmune = immUnits;
			remainingInfection = infUnits;

			if (imm == 0 || inf == 0)
			{
				break;
			}
		}

		startRound(units);
		return getRemainingUnits(units);
	}

	std::pair<std::string, std::string> Day24Puzzle::fastSolve() {
		const auto writeOutput = getVerbose();

		std::vector<Group> units;
		std::unordered_set<int> initiatives;

		int immuneNumber = 1;
		int infectionNumber = 1;

		bool infectionParse = false;
		for (const auto& l : m_InputLines)
		{
			if (l.empty() || StringExtensions::startsWith(l, "Immune"))
			{
				continue;
			}
			if (StringExtensions::startsWith(l, "Infection:"))
			{
				infectionParse = true;
				continue;
			}

			Group& curr = units.emplace_back();
			curr.team = infectionParse ? "Infection" : "Immune";
			if (infectionParse)
			{
				curr.number = infectionNumber++;
			}
			else
			{
				curr.number = immuneNumber++;
			}

			auto p = StringExtensions::splitStringByDelimeter(l, "()");

			if (p.empty()) { continue; }

			if (p.size() == 1)
			{
				const auto loc = l.find("with an attack");
				p.clear();
				p.push_back(l.substr(0, loc-1));
				p.push_back("");
				p.push_back(l.substr(loc));
			}

			{
				const auto& p0 = StringExtensions::splitStringByDelimeter(p[0], " ");
				assert(p0.size() == 7);
				curr.units = std::stoi(p0[0]);
				curr.hp = std::stoi(p0[4]);
			}
			{
				const auto& p1 = StringExtensions::splitStringByDelimeter(p[1], " ,;");
				bool weak = false;
				for (const auto& p : p1)
				{
					if (p == "weak")
					{
						weak = true;
					}
					else if (p == "immune")
					{
						weak = false;
					}
					else if (p == "to")
					{
						continue;
					}
					else if (weak)
					{
						curr.weak.emplace(p);
					}
					else
					{
						curr.immune.emplace(p);
					}
				}
			}

			{
				const auto& p2 = StringExtensions::splitStringByDelimeter(p[2], " ");
				assert(p2.size() == 11);
				curr.attack = std::stoi(p2[5]);
				curr.attackType = p2[6];
				curr.initiative = std::stoi(p2[10]);
				initiatives.emplace(curr.initiative);
			}

		}

		assert(initiatives.size() == units.size());

		const auto& [totalImm, totalInf] = solve(writeOutput, units, 0);

		const auto part1 = totalImm + totalInf;
		int part2 = 0;

		int boost = 0;
		while (part2 <= 0)
		{
			if (writeOutput)
			{
				std::cout << "Running for boost: " << boost << std::endl;
			}
			const auto& [totalImm2, totalInf2] = solve(writeOutput, units, boost);
			part2 = totalImm2;
			boost++;
		}


		return { std::to_string(part1), std::to_string(part2) };
	}
}
