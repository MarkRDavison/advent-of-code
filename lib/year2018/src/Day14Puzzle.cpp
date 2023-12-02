#include <2018/Day14Puzzle.hpp>
#include <Core/StringExtensions.hpp>

namespace TwentyEighteen {
	
	Day14Puzzle::Day14Puzzle() :
		core::PuzzleBase("Chocolate Charts", 2018, 14) {

	}
	Day14Puzzle::~Day14Puzzle() {

	}


	void Day14Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day14Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	void dumpChocolateRecipieInfo(const std::vector<Elf>& elves, const std::vector<ChocolateChartNumber>& recipies)
	{
		for (std::size_t i = 0; i < recipies.size(); ++i)
		{
			if (elves[0].recipie == i)
			{
				std::cout << "(" << recipies[i] << ")";
			}
			else if (elves[1].recipie == i)
			{
				std::cout << "[" << recipies[i] << "]";
			}
			else
			{
				std::cout << " " << recipies[i] << " ";
			}
		}
		std::cout << std::endl;
	}

	void Day14Puzzle::processChocolateRecipieInfo(std::vector<Elf>& elves, std::vector<ChocolateChartNumber>& recipies)
	{
		const auto elf1RecipeValue = recipies[elves[0].recipie];
		const auto elf2RecipeValue = recipies[elves[1].recipie];

		auto newValue = elf1RecipeValue + elf2RecipeValue;

		if (newValue > 9)
		{
			recipies.push_back(1);
			recipies.push_back(newValue - 10);
		}
		else
		{
			recipies.push_back(newValue);
		}

		const auto elf1RecipieOffset = 1 + elf1RecipeValue;
		const auto elf2RecipieOffset = 1 + elf2RecipeValue;

		elves[0].recipie = (elves[0].recipie + elf1RecipieOffset) % recipies.size();
		elves[1].recipie = (elves[1].recipie + elf2RecipieOffset) % recipies.size();
	}

	std::string extractLastNDigitsToString(const std::vector<ChocolateChartNumber>& recipies, std::size_t n)
	{
		std::string res;

		for (std::size_t i = 0; i < n; ++i)
		{
			res += std::to_string(recipies[recipies.size() - n + i]);
		}

		return res;
	}
	std::string Day14Puzzle::solvePart1(ChocolateChartNumber input)
	{
		auto inputString = std::to_string(input);
		std::vector<Elf> elves = {
			Elf{.recipie = 0 }, Elf{.recipie = 1 }
		};

		std::vector<ChocolateChartNumber> recipies = { 3,7 };
		recipies.reserve(input + 10);

		ChocolateChartNumber numIterations = 0;

		std::string part1;

		while (recipies.size() < (std::size_t)(input + 10))
		{
			processChocolateRecipieInfo(elves, recipies);
		}

		for (ChocolateChartNumber i = input; i < input + 10; ++i)
		{
			part1 += std::to_string(recipies[(std::size_t)i]);
		}

		return part1;
	}
	std::string Day14Puzzle::solvePart2(std::string inputStr, bool verbose)
	{
		ChocolateChartNumber input = (ChocolateChartNumber)std::stoll(inputStr);

		std::vector<Elf> elves = {
			Elf{.recipie = 0 }, Elf{.recipie = 1 }
		};

		std::vector<ChocolateChartNumber> recipies = { 3,7 };
		recipies.reserve(1000000000);

		ChocolateChartNumber numIterations = 0;

		while (true)
		{
			processChocolateRecipieInfo(elves, recipies);
			numIterations++;

			if (recipies.size() >= inputStr.size() + 1)
			{
				const auto lastNPlus1 = extractLastNDigitsToString(recipies, inputStr.size() + 1);
				auto found = lastNPlus1.find(inputStr);
				if (found != std::string::npos)
				{
					if (found == 0)
					{
						return std::to_string(recipies.size() - 1 - inputStr.size());
					}
					return std::to_string(recipies.size() - inputStr.size());
				}
			}

			if (verbose)
			{
				if (numIterations % 100000 == 0)
				{
					std::cout << "Part 2 iter: " << numIterations << ", size: " << recipies.size() << std::endl;
				}
			}
		}
	}

	std::pair<std::string, std::string> Day14Puzzle::fastSolve() {

		ChocolateChartNumber input = (ChocolateChartNumber)std::stoll(m_InputLines[0]);

		std::string part1 = solvePart1(input);
		std::string part2 = solvePart2(m_InputLines[0], getVerbose());

		return { part1, part2 };
	}
}
