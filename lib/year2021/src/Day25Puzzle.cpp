#include <2021/Day25Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <Core/Region.hpp>
#include <cassert>

namespace TwentyTwentyOne {

	
	Day25Puzzle::Day25Puzzle() :
		core::PuzzleBase("Sea Cucumber", 2021, 25) {
	}


	void Day25Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day25Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	void printSeaFloor(core::Region<char>& _seaFloor, std::size_t _iterations) {
		std::cout << "===== " << _iterations << " iterations =====" << std::endl;
		for (int y = 0; y <= _seaFloor.maxY; ++y) {
			for (int x = 0; x <= _seaFloor.maxX; ++x) {
				std::cout << _seaFloor.getCell(x, y);
			}
			std::cout << std::endl;
		}
	}
	void clearSeaFloor(core::Region<char>& _seaFloor) {
		for (int y = 0; y <= _seaFloor.maxY; ++y) {
			for (int x = 0; x <= _seaFloor.maxX; ++x) {
				_seaFloor.getCell(x, y) = '.';
			}
		}
	}

	bool iterateEastCucumbers(
		const core::Region<char>& _sourceSeaFloor,
		core::Region<char>& _destinationSeaFloor)
	{
		bool moveMade = false;

		for (int y = 0; y <= _sourceSeaFloor.maxY; ++y) {
			for (int x = 0; x <= _sourceSeaFloor.maxX; ++x) {
				auto& sourceCell = _sourceSeaFloor.getCell(x, y);
				if (sourceCell == 'v') {
					auto& destCell = _destinationSeaFloor.getCell(x, y);
					destCell = 'v';
				}
				else if (sourceCell == '>') {
					int localX = x + 1;
					if (localX > _sourceSeaFloor.maxX) {
						localX = 0;
					}
					const auto& cellNext = _sourceSeaFloor.getCell(localX, y);

					if (cellNext == '.') {
						auto& destCell = _destinationSeaFloor.getCell(localX, y);
						destCell = '>';

						moveMade = true;
					}
					else {
						auto& destCell = _destinationSeaFloor.getCell(x, y);
						destCell = '>';
					}
				}
			}
		}

		return moveMade;
	}

	bool iterateSouthCucumbers(
		const core::Region<char>& _sourceSeaFloor,
		core::Region<char>& _destinationSeaFloor)
	{
		bool moveMade = false;

		for (int y = 0; y <= _sourceSeaFloor.maxY; ++y) {
			for (int x = 0; x <= _sourceSeaFloor.maxX; ++x) {
				auto& sourceCell = _sourceSeaFloor.getCell(x, y);

				if (sourceCell == '>') {
					auto& destCell = _destinationSeaFloor.getCell(x, y);
					destCell = '>';
				}
				else if (sourceCell == 'v') {
					int localY = y + 1;
					if (localY > _sourceSeaFloor.maxY) {
						localY = 0;
					}
					const auto& cellNext = _sourceSeaFloor.getCell(x, localY);

					if (cellNext == '.') {
						auto& destCell = _destinationSeaFloor.getCell(x, localY);
						destCell = 'v';

						moveMade = true;
					}
					else {
						auto& destCell = _destinationSeaFloor.getCell(x, y);
						destCell = 'v';
					}
				}
			}
		}

		return moveMade;
	}

	std::pair<std::string, std::string> Day25Puzzle::fastSolve() {
		core::Region<char> seaFloor1;
		core::Region<char> seaFloor2;

		for (std::size_t y = 0; y < m_InputLines.size(); ++y) {
			for (std::size_t x = 0; x < m_InputLines[y].size(); ++x) {
				seaFloor1.getCell((int)x, (int)y) = m_InputLines[y][x];
				seaFloor2.getCell((int)x, (int)y) = m_InputLines[y][x];
			}
		}


		std::size_t iterations = 0;
		if (getVerbose()) {
			printSeaFloor(seaFloor1, iterations);
		}
		while (true) {
			clearSeaFloor(seaFloor2);
			bool eastMoved = iterateEastCucumbers(seaFloor1, seaFloor2);

			clearSeaFloor(seaFloor1);
			bool southMoved = iterateSouthCucumbers(seaFloor2, seaFloor1);
			iterations++;

			if (getVerbose()) {
				printSeaFloor(seaFloor1, iterations);
			}

			if (!eastMoved && !southMoved) {
				break;
			}
		}

		return { std::to_string(iterations), "*** Free ***"};
	}
}
