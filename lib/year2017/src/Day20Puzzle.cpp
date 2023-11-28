#include <2017/Day20Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <Core/Vector3.hpp>
#include <unordered_map>
#include <algorithm>
#include <numeric>

namespace TwentySeventeen {

	template<typename T>
	struct vector3_hash_fxn {
		std::size_t operator()(const Vector3<T>& _vec) const {
			return  std::hash<T>()(_vec.x) ^ std::hash<T>()(_vec.y) ^ std::hash<T>()(_vec.z);
		}
	};
	
	Day20Puzzle::Day20Puzzle() :
		core::PuzzleBase("Particle Swarm", 2017, 20) {

	}
	Day20Puzzle::~Day20Puzzle() {

	}


	void Day20Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day20Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	struct Particle {
		Vector3i p;
		Vector3i v;
		Vector3i a;
	};

	std::pair<std::string, std::string> Day20Puzzle::fastSolve() {
		std::vector<Particle> particles;

		for (const auto& l : m_InputLines) {
			const auto& parts = StringExtensions::splitStringByDelimeter(l, "=<>,");

			auto& particle = particles.emplace_back();

			particle.p = Vector3i(std::stoi(parts[1]), std::stoi(parts[2]), std::stoi(parts[3]));
			particle.v = Vector3i(std::stoi(parts[5]), std::stoi(parts[6]), std::stoi(parts[7]));
			particle.a = Vector3i(std::stoi(parts[9]), std::stoi(parts[10]), std::stoi(parts[11]));
		}

		std::size_t part1 = 0;
		std::size_t i = 0;
		int minAccMagnitude = std::numeric_limits<int>::max();

		for (const auto& p : particles) {
			const int accMagnitude = std::abs(p.a.x) + std::abs(p.a.y) + std::abs(p.a.z);
			if (minAccMagnitude > accMagnitude) {
				minAccMagnitude = accMagnitude;
				part1 = i;
			}
			i++;
		}

		std::size_t collisionThreshold = 10;
		i = 0;
		while (i < collisionThreshold) {
			std::unordered_map<Vector3i, int, vector3_hash_fxn<int>> positions;
			for (auto& p : particles) {
				p.v += p.a;
				p.p += p.v;

				positions[p.p]++;
			}

			if (positions.size() != particles.size()) {
				i = 0;
				particles.erase(std::remove_if(particles.begin(), particles.end(),
					[&positions](const Particle& _p) -> bool {
						return positions[_p.p] > 1;
					}), particles.end());
			}
			else {
				++i;
			}
		}

		return { std::to_string(part1), std::to_string(particles.size()) };
	}
}
