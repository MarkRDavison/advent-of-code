#include <2021/Day22Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <cassert>
#include <algorithm>
#include <unordered_set>

namespace TwentyTwentyOne {

	std::ostream& operator<<(std::ostream& os, const Cube& _cube) {
		os << "(" << _cube.start.x << ", " << _cube.start.y << ", " << _cube.start.z << ") -> ";
		os << "(" << _cube.end.x << ", " << _cube.end.y << ", " << _cube.end.z << ")";
		os << " (vol: " << _cube.volume() << ")";
		return os;
	}
	template <typename T>
	std::ostream& operator<<(std::ostream& os, const Vector3<T>& _vec) {
		os << "(" << _vec.x << ", " << _vec.y << ", " << _vec.z << ")";
		return os;
	}

	struct ReactorVectorHash {
		std::size_t operator()(const ReactorVector& _vec) const {
			return
				std::hash<ReactorNumber>()(_vec.x) ^
				std::hash<ReactorNumber>()(_vec.y) ^
				std::hash<ReactorNumber>()(_vec.z);
		}
	};
	Day22Puzzle::Day22Puzzle() :
		core::PuzzleBase("Reactor Reboot", 2021, 22) {
	}


	void Day22Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day22Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	bool Day22Puzzle::cubesIntersect(const Cube& _lhs, const Cube& _rhs, Cube& _intersection) {
		const auto r1MinX = std::min(_lhs.start.x, _lhs.end.x);
		const auto r1MaxX = std::max(_lhs.start.x, _lhs.end.x);
		const auto r1MinY = std::min(_lhs.start.y, _lhs.end.y);
		const auto r1MaxY = std::max(_lhs.start.y, _lhs.end.y);
		const auto r1MinZ = std::min(_lhs.start.z, _lhs.end.z);
		const auto r1MaxZ = std::max(_lhs.start.z, _lhs.end.z);

		const auto r2MinX = std::min(_rhs.start.x, _rhs.end.x);
		const auto r2MaxX = std::max(_rhs.start.x, _rhs.end.x);
		const auto r2MinY = std::min(_rhs.start.y, _rhs.end.y);
		const auto r2MaxY = std::max(_rhs.start.y, _rhs.end.y);
		const auto r2MinZ = std::min(_rhs.start.z, _rhs.end.z);
		const auto r2MaxZ = std::max(_rhs.start.z, _rhs.end.z);

		const auto interLeft = std::max(r1MinX, r2MinX);
		const auto interTop = std::max(r1MinY, r2MinY);
		const auto interNear = std::max(r1MinZ, r2MinZ);
		const auto interRight = std::min(r1MaxX, r2MaxX);
		const auto interBottom = std::min(r1MaxY, r2MaxY);
		const auto interFar = std::min(r1MaxZ, r2MaxZ);

		if ((interLeft <= interRight) && (interTop <= interBottom) && (interNear <= interFar)) {
			_intersection = Cube(
				{interLeft, interTop, interNear},
				{interRight, interBottom, interFar}
			);
			return true;
		} else {
			_intersection = Cube();
			return false;
		}
	}

	ReactorNumber solve(const std::vector<Cube>& _input, ReactorNumber _limit) {

		std::vector<Cube> cubes;
		for (const auto& i : _input) {
			if (i.start.x < -_limit || i.end.x > _limit ||
				i.start.y < -_limit || i.end.y > _limit ||
				i.start.z < -_limit || i.end.z > _limit) {
				continue;
			}
			cubes.emplace_back(i);
		}

		std::vector<Cube> onCubes;

		for (const auto& c : cubes) {

			std::vector<Cube> newOnCubes;
			for (const auto& onCube : onCubes) {
				const auto& [splitOccured, splitResults] = Day22Puzzle::split(onCube, c);
				for (const auto& splitCube : splitResults) {
					newOnCubes.push_back(splitCube);
				}
			}
			if (c.action == Cube::Action::ON) {
				newOnCubes.push_back(c);
			}

			onCubes = newOnCubes;
		}

		ReactorNumber vol = 0;
		for (const auto& on : onCubes) {
			ReactorNumber newVol = (on.end.x - on.start.x + 1) * (on.end.y - on.start.y + 1) * (on.end.z - on.start.z + 1);
			std::cout << vol << " + " << newVol << " = " << vol + newVol << std::endl;
			vol += newVol;
		}

		return vol;
	}

	std::pair<std::string, std::string> Day22Puzzle::fastSolve() {
		const auto& parsed = parse(m_InputLines);

		const auto part1 = solve(parsed, 50);
		const auto part2 = -1;// solve(parsed, std::numeric_limits<ReactorNumber>::max());

		return { std::to_string(part1), std::to_string(part2) };
	}

	std::vector<Cube> Day22Puzzle::parse(const std::vector<std::string>& _inputLines) {
		std::vector<Cube> parsed;

		for (const auto& i : _inputLines) {
			const auto& parts = StringExtensions::splitStringByDelimeter(i, " =.,");
			auto& input = parsed.emplace_back();
			assert(parts.size() == 10);
			
			if (parts[0] == "on") {
				input.action = Cube::Action::ON;
			}
			else if (parts[0] == "off") {
				input.action = Cube::Action::OFF;
			}

			input.start.x = std::stoll(parts[2]);
			input.end.x = std::stoll(parts[3]);
			input.start.y = std::stoll(parts[5]);
			input.end.y = std::stoll(parts[6]);
			input.start.z = std::stoll(parts[8]);
			input.end.z = std::stoll(parts[9]);
		}

		return parsed;
	}
	bool Day22Puzzle::cubeInside(const Cube& _lhs, const Cube& _rhs, Cube& _intersection) {
		if (!cubesIntersect(_lhs, _rhs, _intersection)) {
			return false;
		}

		const auto isSmaller = [](const Cube& _lhs, const Cube& _rhs) -> bool {
			if (_lhs.start.x < _rhs.start.x && _rhs.end.x < _lhs.end.x &&
				_lhs.start.y < _rhs.start.y && _rhs.end.y < _lhs.end.y &&
				_lhs.start.z < _rhs.start.z && _rhs.end.z < _lhs.end.z) {
				return true;
			}
			return false;
		};

		if (isSmaller(_lhs, _rhs)) {
			return true;
		}
		else if (isSmaller(_rhs, _lhs)) {
			return true;
		}

		_intersection = {};
		return false;

	}
	
	std::pair<bool, std::vector<Cube>> Day22Puzzle::split(const Cube& _lhs, const Cube& _rhs) {
		assert(_lhs != _rhs);
		Cube intersection;
		std::vector<Cube> newCubes;
		if (!cubesIntersect(_lhs, _rhs, intersection)) {
			return { false, { _lhs, _rhs } };
		}

		newCubes.push_back(Cube(
			{ _lhs.start.x, _lhs.start.y,_lhs.start.z },
			{ _lhs.end.x,_lhs.end.y,intersection.start.z - 1 }
		));
		newCubes.push_back(Cube(
			{ _lhs.start.x, _lhs.start.y, intersection.end.z+1 },
			{ _lhs.end.x,_lhs.end.y,_lhs.end.z }
		));
		newCubes.push_back(Cube(
			{ _lhs.start.x, _lhs.start.y, intersection.start.z},
			{ intersection.start.z-1,_lhs.end.y,intersection.end.z }
		));
		newCubes.push_back(Cube(
			{ intersection.end.x+1,_lhs.start.y,intersection.start.z },
			{ _lhs.end.x,_lhs.end.y,intersection.end.z }
		));
		newCubes.push_back(Cube(
			{ intersection.start.x,_lhs.start.y,intersection.start.z },
			{ intersection.end.x,intersection.end.y+1,intersection.end.z }
		));
		newCubes.push_back(Cube(
			{ intersection.start.x,intersection.end.y+1,intersection.start.z },
			{ intersection.end.x,_lhs.end.y,intersection.end.z }
		));


		std::vector<Cube> newCubes2;

		for (const auto& cube : newCubes) {
			if (cube.start.x <= cube.end.x &&
				cube.start.y <= cube.end.y &&
				cube.start.z <= cube.end.z) {
				newCubes2.push_back(cube);
				newCubes2.back().action = _lhs.action;
			}
		}

		return { true, newCubes2 };
	}
}
