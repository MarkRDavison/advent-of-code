#include <2017/Day21Puzzle.hpp>
#include <zeno-engine/Utility/StringExtensions.hpp>
#include <zeno-engine/Core/Vector2.hpp>
#include <algorithm>
#include <cassert>

namespace TwentySeventeen {
	
	Day21Puzzle::Day21Puzzle() :
		core::PuzzleBase("Fractal Art", 2017, 21) {

	}
	Day21Puzzle::~Day21Puzzle() {

	}


	void Day21Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(ze::StringExtensions::splitStringByDelimeter(ze::StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day21Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}


	static ze::Vector2i getSize(const Art& _art) {
		return { _art.maxX - _art.minX + 1 , _art.maxY - _art.minY + 1 };
	}

	void Day21Puzzle::printArt(Art& _art) {
		if (!getVerbose()) { return; }
		for (int y = _art.minY; y <= _art.maxY; ++y) {
			for (int x = _art.minX; x <= _art.maxX; ++x) {
				std::cout << _art.getCell(x, y);
			}
			std::cout << std::endl;
		}

		auto size = getSize(_art);

		std::cout << "Size: " << size << std::endl;
	}


	Grid Day21Puzzle::flip(const Grid& _grid) {
		auto result(_grid);
		if (result.size() == 2) {
			std::swap(result[0][0], result[1][0]);
			std::swap(result[0][1], result[1][1]);
		}
		else {
			std::swap(result[0][0], result[2][0]);
			std::swap(result[0][1], result[2][1]);
			std::swap(result[0][2], result[2][2]);
		}

		return result;
	}
	Grid Day21Puzzle::mirror(const Grid& _grid) {
		auto result(_grid);

		if (result.size() == 2) {
			std::swap(result[0][0], result[0][1]);
			std::swap(result[1][0], result[1][1]);
		}
		else {
			std::swap(result[0][0], result[0][2]);
			std::swap(result[1][0], result[1][2]);
			std::swap(result[2][0], result[2][2]);
		}

		return result;
	}
	Grid Day21Puzzle::rotate(const Grid& _grid) {
		auto result(_grid);

		if (result.size() == 2) {
			const auto zeroth = result[0][0];

			result[0][0] = result[1][0];
			result[1][0] = result[1][1];
			result[1][1] = result[0][1];
			result[0][1] = zeroth;
		}
		else {
			const auto zeroth = result[0][0];

			std::swap(result[1][2], result[0][1]);
			std::swap(result[0][1], result[1][0]);
			std::swap(result[1][0], result[2][1]);

			std::swap(result[0][0], result[2][0]);
			std::swap(result[2][0], result[2][2]);
			std::swap(result[2][2], result[0][2]);
		}

		return result;
	}
	Grid Day21Puzzle::rotate(const Grid& _grid, std::size_t _iters) {
		auto result(_grid);
		for (std::size_t i = 0; i < _iters; ++i) {
			result = rotate(result);
		}
		return result;
	}

	void iterate(
		Art& _artSource, 
		Art& _artDest, 
		RecipeBook& _book,
		int _srcSize,
		int _destSize) {

		for (int y = 0; y <= _artSource.maxY; y += _srcSize) {
			for (int x = 0; x <= _artSource.maxX; x += _srcSize) {
				std::string current;

				for (int yy = 0; yy < _srcSize; ++yy) {
					for (int xx = 0; xx < _srcSize; ++xx) {
						current += _artSource.getCell(x + xx, y + yy);
					}
					if (yy != _srcSize - 1) {
						current += "/";
					}
				}

				const auto& rec = _book.find(current);
				assert(rec != _book.end());
				const auto& recRes = (*rec).second;

				int rY = 0;
				for (const auto& recResRow : ze::StringExtensions::splitStringByDelimeter(recRes, "/")) {

					for (int rX = 0; rX < (int)recResRow.size(); ++rX) {
						_artDest.getCell((x / _srcSize) * _destSize + rX, (y / _srcSize) * _destSize + rY) = recResRow[rX];
					}

					rY++;
				}
			}
		}
	}

	void iterate(Art& _artSource, Art& _artDest, RecipeBook& _book) {
		auto size = getSize(_artSource);

		assert(size.x == size.y);

		if (size.x % 2 == 0) {
			iterate(_artSource, _artDest, _book, 2, 3);
		}
		else {
			iterate(_artSource, _artDest, _book, 3, 4);
		}

	}

	Art Day21Puzzle::solveForIter(std::size_t _iter) {
		std::vector<Recipe> recipies;
		RecipeBook book;
		for (const auto& l : m_InputLines) {
			const auto& p = ze::StringExtensions::splitStringByDelimeter(l, " ");

			auto& rcp = recipies.emplace_back();
			rcp.src = (Grid)ze::StringExtensions::splitStringByDelimeter(p[0], "/");
			rcp.dst = (Grid)ze::StringExtensions::splitStringByDelimeter(p[2], "/");

			Grid flipped = rcp.src;// flip(rcp.src);
			Grid mirrored = mirror(rcp.src);

			const auto dst = rcp.dst.hash();

			for (std::size_t r = 1; r <= 4; ++r) {
				const auto& flippedRotated = rotate(flipped, r);
				const auto& mirroredRotated = rotate(mirrored, r);

				book[flippedRotated.hash()] = dst;
				book[mirroredRotated.hash()] = dst;
			}
		}

		Art art1;
		Art art2;
		art1.getCell(0, 0) = '.'; art1.getCell(1, 0) = '#'; art1.getCell(2, 0) = '.';
		art1.getCell(0, 1) = '.'; art1.getCell(1, 1) = '.'; art1.getCell(2, 1) = '#';
		art1.getCell(0, 2) = '#'; art1.getCell(1, 2) = '#'; art1.getCell(2, 2) = '#';

		bool buffer = true;
		std::vector< Art*> artBuffer = {
			&art1, &art2
		};
		printArt(art1);

		for (std::size_t i = 0; i < _iter; ++i) {
			if (buffer) {
				if (getVerbose()) {
					std::cout << "Starting iteration " << i + 1 << "/" << _iter << ", size: " << getSize(art1) << std::endl;
				}
				iterate(art1, art2, book);
				printArt(art2);
			}
			else {
				if (getVerbose()) {
					std::cout << "Starting iteration " << i + 1 << "/" << _iter << ", size: " << getSize(art1) << std::endl;
				}
				iterate(art2, art1, book);
				printArt(art1);
			}
			buffer = !buffer;
		}

		if (buffer) {
			return art1;
		}

		return art2;
	}

	std::string Day21Puzzle::fastSolve(std::size_t _iter) {

		std::size_t answer = 0;

		const auto& art = solveForIter(_iter);
		for (int y = 0; y <= art.maxY; ++y) {
			for (int x = 0; x <= art.maxX; ++x) {
				if (art.getCell(x, y) == '#') {
					answer++;
				}
			}
		}

		return std::to_string(answer);
	}
	std::pair<std::string, std::string> Day21Puzzle::fastSolve() {
		return { fastSolve(5) , fastSolve(18) };
	}
}
