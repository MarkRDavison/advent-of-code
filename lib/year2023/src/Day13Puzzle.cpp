#include <2023/Day13Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <algorithm>
#include <numeric>
#include <cassert>

namespace TwentyTwentyThree {
	
	Day13Puzzle::Day13Puzzle() :
		core::PuzzleBase("Point of Incidence", 2023, 13) {
	}


	void Day13Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByLines(StringExtensions::loadFileToString(_initialisationInfo.parameters[0])));
	}

	void Day13Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	typedef std::vector<std::string> Mirror;
	typedef std::vector<Mirror> MirrorVector;

	struct ReflectionInfo
	{
		std::size_t index;
		bool horizontal;
		bool valid{ false };
	};

	std::size_t findReflectionIndex(const Mirror& mirror, int allowedErrors, std::size_t invalidIndex)
	{
		for (std::size_t reflectIndex = 0; reflectIndex < mirror[0].size(); ++reflectIndex)
		{
			int errors = 0;
			for (std::size_t y = 0; y < mirror.size(); ++y)
			{
				std::string left;
				std::string right;

				std::size_t currLeftI = reflectIndex;
				std::size_t currRightI = reflectIndex + 1;

				while (true)
				{
					const auto prevLeftI = currLeftI;
					const auto prevRightI = currRightI;

					if (currRightI >= mirror[y].size() ||
						currLeftI >= mirror[y].size())
					{
						break;
					}

					left += mirror[y][currLeftI];
					right += mirror[y][currRightI];

					currLeftI -= 1;
					currRightI += 1;
				}

				assert(left.size() == right.size());

				if (left.empty() || right.empty())
				{
					errors += 1000;
				}

				for (std::size_t i = 0; i < left.size(); ++i){
					if (left[i] != right[i])
					{
						errors++;
					}
				}
			}

			if (errors <= allowedErrors)
			{
				if (reflectIndex + 1 != invalidIndex)
				{
					return reflectIndex + 1;
				}
			}
		}

		return std::numeric_limits<std::size_t>::max();
	}

	ReflectionInfo findReflectionInfo(const Mirror& mirror, int allowedErrors, const ReflectionInfo& invalidInfo)
	{
		ReflectionInfo info{  };

		std::size_t verticalInvalid = invalidInfo.valid && invalidInfo.horizontal
			? std::numeric_limits<std::size_t>::max()
			: invalidInfo.index;

		// Vertical
		const auto vertInfo = findReflectionIndex(mirror, allowedErrors, verticalInvalid);
		if (vertInfo != std::numeric_limits<std::size_t>::max())
		{
			info.horizontal = false;
			info.valid = true;
			info.index = vertInfo;
			return info;
		}

		// Horizontal
		Mirror rotated;
		rotated.resize(mirror[0].size());

		for (std::size_t sourceY = 0; sourceY < mirror.size(); ++sourceY)
		{
			for (std::size_t sourceX = 0; sourceX < mirror[sourceY].size(); ++sourceX)
			{
				std::size_t destX = sourceY;
				std::size_t destY = mirror[0].size() - 1 - sourceX;

				if (rotated[destY].size() == 0)
				{
					rotated[destY].resize(mirror.size());
				}

				rotated[destY][destX] = mirror[sourceY][sourceX];
			}
		}

		std::size_t horizontalInvalid = invalidInfo.valid && !invalidInfo.horizontal
			? std::numeric_limits<std::size_t>::max()
			: invalidInfo.index;

		const auto horizInfo = findReflectionIndex(rotated, allowedErrors, horizontalInvalid);
		if (horizInfo != std::numeric_limits<std::size_t>::max())
		{
			info.horizontal = true;
			info.valid = true;
			info.index = horizInfo;
			return info;
		}

		return info;
	}

	std::pair<std::string, std::string> Day13Puzzle::fastSolve() {
		MirrorVector mirrors;
		Mirror* curr{ nullptr };
		for (const auto& l : m_InputLines)
		{
			if (l.empty())
			{
				curr = nullptr;
				continue;
			}
			if (curr == nullptr)
			{
				mirrors.emplace_back();
				curr = &mirrors.back();
			}

			curr->push_back(l);
		}

		long long part1 = 0;
		long long part2 = 0;

		ReflectionInfo part1Info{
			.valid = false
		};

		for (const auto& m : mirrors)
		{
			const auto& info1 = findReflectionInfo(m, 0, part1Info);
			if (info1.horizontal)
			{
				part1 += (long long)(info1.index) * 100;
			}
			else
			{
				part1 += (long long)(info1.index);
			}

			const auto& info2 = findReflectionInfo(m, 1, info1);
			if (info2.horizontal)
			{
				part2 += (long long)(info2.index) * 100;
			}
			else
			{
				part2 += (long long)(info2.index);
			}
		}

		return { std::to_string(part1), std::to_string(part2) };
	}
}
