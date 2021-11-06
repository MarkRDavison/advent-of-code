#include <2020/Day21Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <algorithm>
#include <map>

namespace TwentyTwenty {
	
	Day21Puzzle::Day21Puzzle() :
		core::PuzzleBase("Allergen Assessment", 2020, 21) {
	}


	void Day21Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day21Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	std::pair<std::string, std::string> Day21Puzzle::fastSolve() {
		const auto& parsed = Day21Puzzle::parse(m_InputLines);

		const auto part1 = Day21Puzzle::doPart1(parsed);
		const auto part2 = Day21Puzzle::doPart2(parsed);

		return { part1, part2 };
	}

	Day21Parsed Day21Puzzle::parse(const std::vector<std::string>& _inputLines) {
		Day21Parsed parsed;
		std::transform(
			_inputLines.begin(), 
			_inputLines.end(), 
			std::back_inserter(parsed), 
			Day21Puzzle::translate);
		return parsed;
	}
	Day21Struct Day21Puzzle::translate(const std::string& _str) {
		Day21Struct s{};
		bool ingredients = true;
		for (const auto& p : ze::StringExtensions::splitStringByDelimeter(_str, " ,()")) {
			if (p == "contains") {
				ingredients = false;
			}
			else {
				if (ingredients) {
					s.ingredients.insert(p);
				}
				else {
					s.allergens.insert(p);
				}
			}
		}

		return s;
	}

	std::string Day21Puzzle::doPart1(const Day21Parsed& _parsed) {

		std::set<std::string> allergens;
		std::set<std::string> ingredients;
		for (const auto& p : _parsed) {
			for (const auto& i : p.ingredients) {
				ingredients.insert(i);
			}
			for (const auto& a : p.allergens) {
				allergens.insert(a);
			}
		}


		std::set<std::string> safeIngredients(ingredients);

		std::map<std::string, std::set<std::string>> cookbook;
		for (const auto& a : allergens) {
			std::map<std::string, int> ingredientOccurence;
			int allergenOccurence = 0;
			for (const auto& p : _parsed) {
				if (p.allergens.find(a) != p.allergens.end()) {
					allergenOccurence++;
					for (const auto& i : p.ingredients) {
						ingredientOccurence[i]++;
					}
				}
			}
			for (const auto& [ing, occ] : ingredientOccurence) {
				if (occ != 0 && occ == allergenOccurence) {
					cookbook[a].insert(ing);
				}
			}
		}

		std::map<std::string, std::string> identifiedAllergens;
		while (identifiedAllergens.size() != allergens.size()) {
			for (const auto& [allergen, ingredients] : cookbook) {
				if (ingredients.size() == 1) {
					identifiedAllergens[allergen] = *ingredients.begin();
					for (auto& [a2, i2] : cookbook) {
						i2.erase(identifiedAllergens[allergen]);
						safeIngredients.erase(identifiedAllergens[allergen]);
					}
					break;
				}
			}
		}

		int safeIngredientCount = 0;
		for (const auto& p : _parsed) {
			for (const auto& i : p.ingredients) {
				if (safeIngredients.find(i) != safeIngredients.end()) {
					safeIngredientCount++;
				}
			}
		}

		std::string part2;
		for (const auto& [a, i] : identifiedAllergens) {
			if (!part2.empty()) {
				part2 += ',';
			}
			part2 += i;
		}
		std::cout << "Part 2:" << part2 << std::endl;

		return std::to_string(safeIngredientCount);
	}
	std::string Day21Puzzle::doPart2(const Day21Parsed& _parsed) {
		return "";
	}
}
