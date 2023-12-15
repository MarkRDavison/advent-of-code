#include <2023/Day15Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <cassert>
#include <array>

namespace TwentyTwentyThree {
	
	Day15Puzzle::Day15Puzzle() :
		core::PuzzleBase("Lens Library", 2023, 15) {
	}


	void Day15Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day15Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}
	
	int Day15Puzzle::hash(const std::string& str)
	{
		long long acc = 0;

		for (const char c : str)
		{
			long long ascii = (long long)(c);
			acc += ascii;
			acc *= 17;
			acc %= 256;
		}

		return (int)acc;
	}

	typedef std::pair<std::string, int> Lens;
	typedef std::vector<Lens> Box;

	bool isLensLabelInBox(const Box& box, const Lens& lens)
	{
		for (const auto& boxLens : box)
		{
			if (boxLens.first == lens.first)
			{
				return true;
			}
		}

		return false;
	}

	void eraseByLabel(Box& box, const std::string& label)
	{
		box.erase(
			std::remove_if(
				box.begin(),
				box.end(),
				[&label](const Lens& lens) -> bool
				{
					return lens.first == label;
				}),
			box.end());
	}

	void updateLensValue(Box& box, const Lens& lens)
	{
		for (auto& [label, value] : box)
		{
			if (label == lens.first)
			{
				value = lens.second;
			}
		}
	}

	std::pair<std::string, std::string> Day15Puzzle::fastSolve() {
		const auto& instr = StringExtensions::splitStringByDelimeter(m_InputLines[0], ",");

		std::array<Box, 256> boxes;

		int part1 = 0;
		for (const auto& i : instr)
		{
			part1 += hash(i);
		}

		for (const auto& i : instr)
		{
			const auto dashIndex = i.find('-');
			const auto equalsIndex = i.find('=');

			const auto& parts = StringExtensions::splitStringByDelimeter(i, "-=");
			assert(parts.size() >= 1);

			const auto& label = parts[0];
			const auto boxIndex = (std::size_t)hash(label);
			assert(0 <= boxIndex && boxIndex <= 255);

			auto& box = boxes[boxIndex]; 
			if (equalsIndex != std::string::npos)
			{
				const Lens lens = { label, std::stoi(parts[1]) };
				if (isLensLabelInBox(box, lens))
				{
					updateLensValue(box, lens);
				}
				else
				{
					box.push_back(lens);
				}
			}
			else if (dashIndex != std::string::npos)
			{
				eraseByLabel(box, label);
			}
			else
			{
				assert(false);
			}

			if (getVerbose())
			{
				std::cout << "After \"" << i << "\":\n";
				std::size_t boxI = 0;
				for (const auto& box : boxes)
				{
					if (box.empty())
					{
						boxI++;
						continue;
					}

					std::cout << "Box " << boxI << ":";

					for (const auto& lens : box)
					{
						std::cout << " [" << lens.first << " " << lens.second << "]";
					}

					std::cout << "\n";

					boxI++;
				}

				std::cout << std::endl;
			}
		}

		long long part2 = 0;
		for (std::size_t i = 0; i < boxes.size(); ++i)
		{
			for (std::size_t j = 0; j < boxes[i].size(); ++j)
			{
				const long long lensSum = (i + 1) * (j + 1) * boxes[i][j].second;
				part2 += lensSum;
			}
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
