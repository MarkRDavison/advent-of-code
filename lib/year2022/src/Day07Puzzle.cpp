#include <2022/Day07Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <cassert>
#include <unordered_map>

namespace TwentyTwentyTwo {
	
	Day07Puzzle::Day07Puzzle() :
		core::PuzzleBase("No Space Left On Device", 2022, 7) {
	}


	void Day07Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day07Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct Directory {
		std::string name;
		std::vector<Directory *> children;
		Directory* parent{ nullptr };

		long size{ 0 };
		long childrenSize{ 0 };
	};

	void updateFileSizes(Directory* _current) 
	{
		for (auto d : _current->children)
		{
			updateFileSizes(d);
			_current->childrenSize += d->size + d->childrenSize;
		}
	}

	void identifyBelowThreshold(Directory* _current, std::vector<Directory*>& _identified)
	{
		for (auto d : _current->children)
		{
			identifyBelowThreshold(d, _identified);
		}

		if (_current->size + _current->childrenSize <= 100000)
		{
			_identified.push_back(_current);
		}
	}

	long solvePart1(Directory* _root)
	{
		std::vector<Directory*> identified;
		identifyBelowThreshold(_root, identified);

		long answer = 0;

		for (const auto dir : identified)
		{
			auto size = dir->size + dir->childrenSize;
			answer += size;
		}

		return answer;
	}

	void fetchSizes(Directory* _current, std::unordered_map<std::string, long>& _sizes)
	{
		_sizes[_current->name] = _current->size + _current->childrenSize;
		for (auto d : _current->children)
		{
			fetchSizes(d, _sizes);
		}
	}

	long solvePart2(Directory* _root)
	{
		const long TotalSize = 70000000;
		const long FreeSpaceNeeded = 30000000;

		const long usedSpace = _root->size + _root->childrenSize;
		const long unusedSpace = TotalSize - usedSpace;

		const long spaceToFree = FreeSpaceNeeded - unusedSpace;

		std::unordered_map<std::string, long> dirSizes;
		fetchSizes(_root, dirSizes);

		long min = std::numeric_limits<long>::max();

		for (const auto& [name, size] : dirSizes)
		{
			if (size >= spaceToFree && min > size)
			{
				min = size;
			}
		}

		return min;
	}

	std::pair<std::string, std::string> Day07Puzzle::fastSolve() {
		assert("$ cd /" == m_InputLines[0]);

		Directory* root = new Directory();
		root->name = "/";

		Directory* current = root;

		std::vector<std::string> location{ "/" };

		bool first = true;
		for (const auto& l : m_InputLines)
		{
			if (first) {
				first = false;
				continue;
			}

			if (StringExtensions::startsWith(l, "$"))
			{
				if (StringExtensions::startsWith(l, "$ cd ")) 
				{
					const auto& p = StringExtensions::splitStringByDelimeter(l, " ");
					const auto newDirectory = p[2];

					if (newDirectory == "..")
					{
						current = current->parent;
					}
					else
					{
						location.push_back(p[2]);
						auto dir = new Directory();
						dir->name = newDirectory;
						current->children.push_back(dir);
						dir->parent = current;
						current = dir;
					}
				}
			}
			else if (StringExtensions::startsWith(l, "dir "))
			{
				// Directory				
			}
			else
			{
				// File
				const auto& p = StringExtensions::splitStringByDelimeter(l, " ");
				const auto size = std::stol(p[0]);
				const auto filename = p[1];

				current->size += size;
			}
		}

		updateFileSizes(root);

		const auto part1 = solvePart1(root);
		const auto part2 = solvePart2(root);

		return { std::to_string(part1), std::to_string(part2) };
	}
}
