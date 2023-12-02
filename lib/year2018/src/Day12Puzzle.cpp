#include <2018/Day12Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_set>
#include <unordered_map>
#include <cassert>

namespace TwentyEighteen {
	
	Day12Puzzle::Day12Puzzle() :
		core::PuzzleBase("Subterranean Sustainability", 2018, 12) {

	}
	Day12Puzzle::~Day12Puzzle() {

	}


	void Day12Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day12Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, long long> processGeneration(
		const std::unordered_map<std::string, bool>& notes,
		std::string state,
		long long zero
	)
	{
		zero += 5;

		state = "....." + state + ".....";
		std::string newState = std::string(state.size(), '.');
		for (std::size_t i = 2; i < state.size() - 2; ++i)
		{
			const auto curr = state.substr(i - 2, 5);
			const auto& res = notes.find(curr);
			if (res != notes.end())
			{
				const auto isPlantNext = (*res).second;
				if (isPlantNext)
				{
					newState[i] = '#';
				}
			}
		}

		const auto firstPlant = newState.find('#');

		if (firstPlant > 0)
		{
			zero -= firstPlant;
			const auto lastPlant = newState.find_last_of('#');
			const auto size = lastPlant - firstPlant;
			newState = newState.substr(firstPlant, size + 1);
		}

		

		return { newState, zero };
	}

	std::pair<std::string, std::string> Day12Puzzle::fastSolve() {

		const std::string initialState = m_InputLines[0].substr(15);

		std::unordered_map<std::string, bool> notes;
		std::unordered_set<long long> plants;

		for (long long i = 0; i < initialState.size(); ++i)
		{
			if (initialState[i] == '#')
			{
				plants.emplace(i);
			}
		}

		for (std::size_t i = 2; i < m_InputLines.size(); ++i)
		{
			const auto& parts = StringExtensions::splitStringByDelimeter(m_InputLines[i], " =>");

			notes.emplace(parts[0], parts[1] == "#");
		}



		std::cout << "0:  " << initialState << std::endl;
		long long zero = 0;
		long long generation = 0;
		std::string state(initialState);
		while (generation < 20)
		{
			const auto& [newState, newZero] = processGeneration(notes, state, zero);
			generation++;
			state = newState;
			zero = newZero;
			std::cout << generation << ":  " << state << "\t\t\t\t\t\t - zero: " << -zero << std::endl;
		}

		long long part1 = 0;

		for (long long i = 0; i < state.size(); ++i)
		{
			if (state[i] == '#')
			{
				part1 += (i - zero);
			}
		}

		return { std::to_string(part1), "Part 2"};
	}
}
