#include <2022/Day17Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <cassert>
#include <Core/Region.hpp>
#include <zeno-engine/Core/Vector2.hpp>


namespace TwentyTwentyTwo {
	
	Day17Puzzle::Day17Puzzle() :
		core::PuzzleBase("Pyroclastic Flow", 2022, 17) {
	}


	void Day17Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day17Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct Rock {
		int width{ 0 };
		int height{ 0 };

		std::vector<std::string> shape;
	};

	struct ChamberCell {
		char c{ '.' };
	};

	bool print(core::Region<ChamberCell>& _chamber, Rock *_activeRock, const ze::Vector2i& _rockBottomLeft)
	{
		std::vector<std::string> display;

		for (int y = 0; y <= std::max(_chamber.maxY, _rockBottomLeft.y + 4); ++y)
		{
			std::string row = ".......";
			for (int x = 0; x < 7; ++x)
			{
				const auto& cell = _chamber.getCell(x, y);
				row[(unsigned)x] = cell.c;
			}
			display.push_back(row);
		}

		if (_activeRock != nullptr)
		{

			for (int y = 0; y < _activeRock->height; ++y)
			{
				for (int x = _rockBottomLeft.x; x < _rockBottomLeft.x + _activeRock->width; ++x)
				{
					auto rockCell = _activeRock->shape[y][x - _rockBottomLeft.x];
					if (rockCell == '#')
					{
						rockCell = '@';
					}
					display[_rockBottomLeft.y + _activeRock->height - 1 - y][x] = rockCell;
				}
			}
		}

		for (std::size_t i = display.size(); i > 0; --i)
		{
			std::cout << "|" << display[i - 1] << "|" << std::endl;
		}
		std::cout << "+-------+" << std::endl << std::endl;

		return false;
	}

	bool isValidAt(core::Region<ChamberCell>& _chamber, Rock* _activeRock, const ze::Vector2i& _rockBottomLeft)
	{
		if (_rockBottomLeft.y < 0)
		{
			return false;
		}
		for (int y = 0; y < _activeRock->height; ++y)
		{
			for (int x = _rockBottomLeft.x; x < _rockBottomLeft.x + _activeRock->width; ++x)
			{
				auto rockCell = _activeRock->shape[y][x - _rockBottomLeft.x];
				if (rockCell == '#')
				{
					auto chamberCell = _chamber.getCell(x, _rockBottomLeft.y + _activeRock->height - 1 - y).c;

					if (chamberCell == '#')
					{
						return false;
					}
				}
			}
		}

		return true;
	}

	std::pair<std::string, std::string> Day17Puzzle::fastSolve() {
		
		std::vector<Rock> rocks {
			Rock{.width = 4, .height = 1, .shape =
			{
				"####"
			}},
			Rock{.width = 3, .height = 3, .shape =
			{
				".#.", "###", ".#."
			}},
			Rock{.width = 3, .height = 3, .shape =
			{
				"..#", "..#", "###"
			}},
			Rock{.width = 1, .height = 4, .shape =
			{
				"#", "#", "#", "#"
			}},
			Rock{.width = 2, .height = 2, .shape =
			{
				"##", "##"
			}},
		};

		core::Region<ChamberCell> chamber;
		for (int y = 0; y < 4; ++y)
		{
			for (int x = 0; x < 7; ++x)
			{
				chamber.getCell(x, y).c = '.';
			}
		}

		int highestSettledRock = -1;
		
		ze::Vector2i activeRockBottomLeft = { 2, highestSettledRock + 4 };

		std::size_t activeRockIndex = 0;

		int rocksStopped = 0;
		std::size_t i = 0;
		while (true)
		{
			const auto jet = m_InputLines[0][i];

			i = (i + 1) % m_InputLines[0].size();

			Rock* activeRock = &rocks[activeRockIndex];

			//print(chamber, activeRock, activeRockBottomLeft);

			if (jet == '<')
			{
				auto prevX = activeRockBottomLeft.x;
				activeRockBottomLeft.x = std::max(0, activeRockBottomLeft.x - 1);
				if (!isValidAt(chamber, activeRock, activeRockBottomLeft))
				{
					activeRockBottomLeft.x = prevX;
				}
			}
			else if (jet == '>')
			{
				auto prevX = activeRockBottomLeft.x;
				activeRockBottomLeft.x = std::min(6 - activeRock->width + 1, activeRockBottomLeft.x + 1);
				if (!isValidAt(chamber, activeRock, activeRockBottomLeft))
				{
					activeRockBottomLeft.x = prevX;
				}
			}
			else { assert(false); }

			//print(chamber, activeRock, activeRockBottomLeft);

			activeRockBottomLeft.y -= 1;

			bool valid = isValidAt(chamber, activeRock, activeRockBottomLeft);
			if (!valid)
			{
				{
					for (int y = 0; y < activeRock->height; ++y)
					{
						for (int x = 0; x < activeRock->width; ++x)
						{
							const auto chamberX = x + activeRockBottomLeft.x;
							const auto chamberY = activeRock->height - y + activeRockBottomLeft.y;
							highestSettledRock = std::max(highestSettledRock, chamberY);



							auto& cell = chamber.getCell(chamberX, chamberY);
							cell.c = activeRock->shape[y][x];
						}
					}

					//print(chamber, nullptr, activeRockBottomLeft);

					activeRockIndex = (activeRockIndex + 1) % rocks.size();

					activeRockBottomLeft = { 2, highestSettledRock + 4 };
					rocksStopped++;
					std::cout << "Rocks stopped: " << rocksStopped << std::endl;
					if (rocksStopped == 2022)
					{
						return { std::to_string(highestSettledRock + 1) , ""};
					}
				}
			}
		}

		return { "Part 1", "Part 2" };
	}
}
