#include <2018/Day08Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <span>

namespace TwentyEighteen {
	
	Day08Puzzle::Day08Puzzle() :
		core::PuzzleBase("Memory Maneuver", 2018, 8) {

	}
	Day08Puzzle::~Day08Puzzle() {

	}


	void Day08Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day08Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	void recurse(const std::span<int>& _span, std::size_t& _index, int& _metadataSum, bool _part2)
	{
		const auto numChildren = _span[_index + 0];
		const auto numMetadata = _span[_index + 1];

		_index += 2;

		std::vector<int> childMetadata;
		for (int i = 0; i < numChildren; ++i)
		{
			int childMetadataValue = 0;
			recurse(_span, _index, childMetadataValue, _part2);
			childMetadata.push_back(childMetadataValue);
		}


		std::vector<int> selfMetadata;
		for (int i = 0; i < numMetadata; ++i)
		{
			selfMetadata.push_back(_span[_index + i]);
		}

		if (!_part2)
		{
			_metadataSum += std::accumulate(selfMetadata.begin(), selfMetadata.end(), 0);
			_metadataSum += std::accumulate(childMetadata.begin(), childMetadata.end(), 0);
		}
		else
		{
			for (const auto& selfMetadataValue : selfMetadata)
			{
				if (numChildren == 0)
				{
					_metadataSum += selfMetadataValue;
				}
				else
				{
					std::size_t childMetadataIndex = (std::size_t)selfMetadataValue - 1;
					if (0 <= childMetadataIndex && childMetadataIndex < childMetadata.size())
					{
						_metadataSum += childMetadata[childMetadataIndex];
					}
				}
			}
		}

		_index += numMetadata;
	}

	std::pair<std::string, std::string> Day08Puzzle::fastSolve() {
		std::vector<int> parsed;
		for (const auto& p : ze::StringExtensions::splitStringByDelimeter(m_InputLines[0], " "))
		{
			parsed.push_back(std::stoi(p));
		}

		int part1 = 0;
		int part2 = 0;
		{
			std::size_t index = 0;
			recurse(std::span<int>(parsed), index, part1, false);
		}
		{
			std::size_t index = 0;
			recurse(std::span<int>(parsed), index, part2, true);
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
