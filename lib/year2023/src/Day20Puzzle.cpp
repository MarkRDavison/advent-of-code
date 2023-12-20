#include <2023/Day20Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <queue>

namespace TwentyTwentyThree {
	
	Day20Puzzle::Day20Puzzle() :
		core::PuzzleBase("Pulse Propagation", 2023, 20) {
	}


	void Day20Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day20Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	enum class SignalType
	{
		LOW = 0,
		HIGH = 1
	};

	struct Module
	{
		std::string name;
		enum class ModuleType
		{
			BROADCASTER,
			FLIP_FLOP,
			CONJUNCTION,
			TEST
		} type;

		bool on{ false };

		std::unordered_map<std::string, SignalType> lastSignals;

		std::vector<std::string> destinations;
	};

	struct QueuedSignal
	{
		std::string sourceName;
		std::string destName;
		SignalType type;
	};

	typedef std::unordered_map<std::string, Module> Modules;
	typedef std::unordered_map<SignalType, long long> Stats;
	typedef std::queue<QueuedSignal> SignalQueue;
	void queueSignal(
		SignalQueue& queue, 
		Stats& stats, 
		Modules& modules,
		const std::string& sourceModuleName,
		const std::string& destModuleName, 
		SignalType type);

	void handleBroadcast(
		SignalQueue& queue, 
		Stats& stats, 
		Modules& modules, 
		const Module& module, 
		SignalType type)
	{
		assert(module.type == Module::ModuleType::BROADCASTER);

		for (const auto& d : module.destinations)
		{
			queueSignal(queue, stats, modules, module.name, d, type);
		}
	}

	void handleFlipFlop(
		SignalQueue& queue, Stats& stats, Modules& modules, Module& module, SignalType type)
	{
		assert(module.type == Module::ModuleType::FLIP_FLOP);
		if (type == SignalType::HIGH) { return; }

		module.on = !module.on;

		for (const auto& d : module.destinations)
		{
			queueSignal(queue, stats, modules, module.name, d, module.on ? SignalType::HIGH : SignalType::LOW);
		}
	}

	void handleConjunction(
		SignalQueue& queue, 
		Stats& stats, 
		Modules& modules, 
		Module& module, 
		SignalType type, 
		const std::string& source)
	{
		assert(module.type == Module::ModuleType::CONJUNCTION);

		assert(module.lastSignals.contains(source));
		module.lastSignals[source] = type;

		bool allHigh = true;

		for (const auto& [updateName, type] : module.lastSignals)
		{
			if (module.lastSignals.at(updateName) != SignalType::HIGH)
			{
				allHigh = false;
			}
		}

		for (const auto& d : module.destinations)
		{
			queueSignal(queue, stats, modules, module.name, d, allHigh ? SignalType::LOW : SignalType::HIGH);
		}
	}

	void queueSignal(
		SignalQueue& queue, 
		Stats& stats, 
		Modules& modules,
		const std::string& sourceModuleName,
		const std::string& destModuleName,
		SignalType type)
	{
		queue.push(QueuedSignal
			{
			.sourceName = sourceModuleName,
			.destName = destModuleName,
			.type = type
			});
	}

	void runIteration(Modules& modules, Stats& stats)
	{
		SignalQueue queue;

		queueSignal(queue, stats, modules, "button", "broadcaster", SignalType::LOW);

		while (!queue.empty())
		{
			const auto signal = queue.front(); queue.pop();

			stats[signal.type]++;
			auto& module = modules.at(signal.destName);
			switch (module.type)
			{
			case Module::ModuleType::BROADCASTER:
				handleBroadcast(queue, stats, modules, module, signal.type);
				break;
			case Module::ModuleType::FLIP_FLOP:
				handleFlipFlop(queue, stats, modules, module, signal.type);
				break;
			case Module::ModuleType::CONJUNCTION:
				handleConjunction(queue, stats, modules, module, signal.type, signal.sourceName);
				break;
			case Module::ModuleType::TEST:
				break;
			default:
				assert(false);
			}
		}
	}

	long long solvePart2(Modules& modules)
	{
		if (!modules.contains("rx"))
		{
			return -1;
		}

		Stats stats;

		const auto& loopStartNames = modules.at("broadcaster").destinations;
		std::vector<std::string> loopEndNames;
		for (const auto& [name, module] : modules)
		{
			for (const auto& d : module.destinations)
			{
				if (d == "rx")
				{
					loopEndNames.push_back(name);
				}
			}
		}
		
		assert(loopEndNames.size() == 1);
		if (loopEndNames.size() != 1) { return -1; }
		const auto loopEndName = loopEndNames[0];
		loopEndNames.clear();
		for (const auto& [name, module] : modules)
		{
			for (const auto& d : module.destinations)
			{
				if (d == loopEndName)
				{
					loopEndNames.push_back(name);
				}
			}
		}

		std::unordered_map<std::string, unsigned long long> previousCycleLengths;
		std::unordered_map<std::string, unsigned long long> discoveredCycleLengths;

		for (unsigned long long i = 1; ; ++i)
		{
			SignalQueue queue;

			queueSignal(queue, stats, modules, "button", "broadcaster", SignalType::LOW);

			while (!queue.empty())
			{
				const auto signal = queue.front(); queue.pop();

				{
					stats[signal.type]++;
					auto& module = modules.at(signal.destName);
					switch (module.type)
					{
					case Module::ModuleType::BROADCASTER:
						handleBroadcast(queue, stats, modules, module, signal.type);
						break;
					case Module::ModuleType::FLIP_FLOP:
						handleFlipFlop(queue, stats, modules, module, signal.type);
						break;
					case Module::ModuleType::CONJUNCTION:
						handleConjunction(queue, stats, modules, module, signal.type, signal.sourceName);
						break;
					case Module::ModuleType::TEST:
						break;
					default:
						assert(false);
					}
				}

				if (signal.destName == loopEndName && signal.type == SignalType::HIGH)
				{
					if (!discoveredCycleLengths.contains(signal.sourceName))
					{
						if (previousCycleLengths.contains(signal.sourceName))
						{
							discoveredCycleLengths[signal.sourceName] = i - previousCycleLengths[signal.sourceName];

							if (discoveredCycleLengths.size() == loopEndNames.size())
							{
								unsigned long long curr = 1;
								for (const auto [name, cycleLength] : discoveredCycleLengths)
								{
									curr = std::lcm(curr, cycleLength);
								}
								return curr;
							}
						}
						else
						{
							previousCycleLengths[signal.sourceName] = i;
						}
					}
				}
			}
		}

		return -1;
	}
	long long solvePart1(Modules& modules)
	{
		Stats stats;

		long long part1Repetitions = 1000;

		for (long long i = 0; i < part1Repetitions; ++i)
		{
			runIteration(modules, stats);
		}

		return stats.at(SignalType::HIGH) * stats.at(SignalType::LOW);
	}

	std::pair<std::string, std::string> Day20Puzzle::fastSolve() {
		Modules modules;

		for (const auto& l : m_InputLines)
		{
			const auto& moduleParts = StringExtensions::splitStringByDelimeter(l, " ,");

			bool flipflop = moduleParts[0][0] == '%';
			bool inverter = moduleParts[0][0] == '&';
			bool broadcaster = moduleParts[0] == "broadcaster";

			Module newModule;
			newModule.name = moduleParts[0];
			if (broadcaster)
			{
				newModule.type = Module::ModuleType::BROADCASTER;
			}
			else if (inverter)
			{
				newModule.type = Module::ModuleType::CONJUNCTION;
				newModule.name = newModule.name.substr(1);
			}
			else if (flipflop)
			{
				newModule.type = Module::ModuleType::FLIP_FLOP;
				newModule.name = newModule.name.substr(1);
			}
			else
			{
				assert(false);
			}

			assert(moduleParts[1] == "->");

			for (std::size_t i = 2; i < moduleParts.size(); ++i)
			{
				newModule.destinations.push_back(moduleParts[i]);
			}

			modules[newModule.name] = newModule;
		}

		for (auto& [name, module] : modules)
		{
			if (module.type == Module::ModuleType::CONJUNCTION)
			{
				for (const auto& [nameInner, moduleInner] : modules)
				{
					for (const auto& dInner : moduleInner.destinations)
					{
						if (dInner == name)
						{
							module.lastSignals[nameInner] = SignalType::LOW;
						}
					}
				}
			}
		}
		for (const auto& [name, module] : modules)
		{
			for (const auto& d : module.destinations)
			{
				if (!modules.contains(d))
				{
					Module newModule;
					newModule.name = d;
					newModule.type = Module::ModuleType::TEST;
					modules[newModule.name] = newModule;
				}
			}
		}

		const auto part1 = solvePart1(modules);
		const auto part2 = solvePart2(modules);

		return { std::to_string(part1), std::to_string(part2) };
	}
}
