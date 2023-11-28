#ifndef INCLUDED_ADVENT_OF_CODE_CORE_PATHFINDING_HPP_
#define INCLUDED_ADVENT_OF_CODE_CORE_PATHFINDING_HPP_

#include <numeric>
#include <Core/Vector2.hpp>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <vector>
#include <queue>

namespace std {
	template<>
	struct hash<Vector2i> {
		size_t operator()(const Vector2i& obj) const {
			return std::hash<int>()(obj.x) ^ std::hash<int>()(obj.y);
		}
	};
	template<class T>
	struct hash<Vector2<T>> {
		size_t operator()(const Vector2<T>& obj) const {
			return std::hash<T>()(obj.x) ^ std::hash<T>()(obj.y);
		}
	};
}
namespace internal {

	template<typename Coordinate, typename PriorityValue >
	struct PriorityQueue {

		typedef std::pair<PriorityValue, Coordinate> CoordinatePriorityElement;
		struct PairCompareFxn {
			bool operator()(CoordinatePriorityElement _lhs, CoordinatePriorityElement _rhs) {
				return _lhs.first > _rhs.first;
			}
		};
		std::priority_queue<CoordinatePriorityElement, std::vector<CoordinatePriorityElement>, PairCompareFxn> elements;

		inline bool empty() const {
			return elements.empty();
		}

		inline void put(Coordinate item, PriorityValue priority) {
			elements.emplace(priority, item);
		}

		Coordinate get() {
			Coordinate best_item = elements.top().second;
			elements.pop();
			return best_item;
		}
	};

	struct EdgeGraph {
		std::unordered_map<std::string, std::unordered_set<std::string>> edges;
		std::unordered_map<std::string, float> weights;
		std::unordered_set<std::string> nodes;

		std::unordered_set<std::string> neighbours(const std::string& _id) {
			return edges.at(_id);
		}

		float cost(const std::string& _from, const std::string& _to) {
			return weights[_to + "_" + _from];
		}

		float heuristic(const std::string& _from, const std::string& _to) {
			return static_cast<float>(std::abs(weights[_from] - weights[_to]));
		}
	};

	template <typename Cell>
	struct CartesianGraph {

		std::vector<Vector2i> neighbours(const Vector2i& _id) {
			if (cells.empty() || cells[0].empty()) {
				return {};
			}

			const int height = (int)cells.size();
			const int width = (int)cells[0].size();

			std::vector<Vector2i> n;

			if (_id.y > 0) {
				if (cells[_id.y - 1][_id.x].valid()) {
					n.push_back({ _id.x, _id.y - 1 });
				}
			}
			if (_id.x > 0) {
				if (cells[_id.y][_id.x - 1].valid()) {
					n.push_back({ _id.x - 1, _id.y });
				}
			}
			if (_id.x + 1 < width) {
				if (cells[_id.y][_id.x + 1].valid()) {
					n.push_back({ _id.x + 1, _id.y });
				}
			}
			if (_id.y + 1 < height) {
				if (cells[_id.y + 1][_id.x].valid()) {
					n.push_back({ _id.x, _id.y + 1 });
				}
			}

			return n;
		}

		float cost(const Vector2i& _from, const Vector2i& _to) {
			return cells[_from.y][_from.x].costTo(cells[_to.y][_to.x]);
		}

		float heuristic(const Vector2i& _a, const Vector2i& _b) {
			return static_cast<float>(std::abs(_a.x - _b.x) + std::abs(_a.y - _b.y));
		}

		std::vector<std::vector<Cell>> cells;
	};

	template <typename Graph, typename Node>
	std::unordered_map<Node, Node> breadthFirstSearch(Graph& _graph, Node _start, Node _end) {
		std::queue<Node> toVisit;
		toVisit.push(_start);

		std::unordered_map<Node, Node> originatingNodes;
		originatingNodes[_start] = _start;

		while (!toVisit.empty()) {
			Node current = toVisit.front();
			toVisit.pop();

			if (current == _end) {
				break;
			}

			for (const Node& next : _graph.neighbours(current)) {
				if (originatingNodes.count(next) == 0) {
					toVisit.push(next);
					originatingNodes[next] = current;
				}
			}
		}

		return originatingNodes;
	}
	template <typename Graph, typename Node>
	std::unordered_map<Node, int> floodFill(Graph& _graph, Node _start) {
		std::queue<std::pair<Node, int>> toVisit;
		toVisit.push({ _start, 0 });

		std::unordered_map<Node, int> costs;
		costs[_start] = 0;

		while (!toVisit.empty()) {
			const auto [current, cost] = toVisit.front();
			toVisit.pop();

			for (const Node& next : _graph.neighbours(current)) {
				if (costs.count(next) == 0) {
					toVisit.push({ next, cost + 1 });
					costs[next] = cost + 1;
				}
				else {
					auto prevCost = costs[next];
					if (prevCost > cost + 1) {
						costs[next] = cost + 1;
						toVisit.push({ next, cost + 1 });
					}
				}
			}
		}

		return costs;
	}

	template <typename Graph, typename Node>
	std::unordered_map<Node, Node> breadthFirstSearchWithMaxSteps(Graph& _graph, Node _start, int _maxSteps) {
		std::queue<std::pair<Node, int>> toVisit;
		toVisit.push({ _start, 0 });

		std::unordered_map<Node, Node> originatingNodes;
		std::unordered_map<Node, int> costs;
		originatingNodes[_start] = _start;

		while (!toVisit.empty()) {
			const auto [current, cost] = toVisit.front();
			toVisit.pop();
			if (cost >= _maxSteps) {
				continue;
			}

			for (const Node& next : _graph.neighbours(current)) {
				if (costs.find(next) != costs.end()) {
					auto previousCost = costs[next];
					if (previousCost > cost + 1) {
						costs[next] = cost + 1;
						toVisit.push({ next, cost + 1 });
						originatingNodes[next] = current;
					}
				}
				else {
					toVisit.push({ next, cost + 1 });
					originatingNodes[next] = current;
					costs[next] = cost + 1;
				}
			}
		}
		
		return originatingNodes;
	}

	template <typename Graph, typename Node>
	std::vector<std::pair<Node, std::pair<unsigned, float>>> depthFirstSearch(Graph& _graph, Node _start, Node _end) {
		std::unordered_set<Node> visited;
		visited.insert(_start);
		return depthFirstSearchRecursion(_graph, visited, _start, _end, std::make_pair(0, 0.0f));
	}

	template <typename Graph, typename Node>
	std::vector<std::pair<Node, std::pair<unsigned, float>>> depthFirstSearchRecursion(Graph& _graph, std::unordered_set<Node>& _visited, Node _start, Node _end, std::pair<unsigned, float> _depthCost) {
		std::vector<std::pair<Node, std::pair<unsigned, float>>> results{ {_start, _depthCost} };

		if (_start == _end) {
			return results;
		}

		for (const auto& n : _graph.neighbours(_start)) {
			if (_visited.find(n) == _visited.end()) {
				_visited.insert(n);
				const auto& childResult = depthFirstSearchRecursion(_graph, _visited, n, _end, std::make_pair(_depthCost.first + 1, _depthCost.second + _graph.cost(_start, n)));
				for (const auto& cr : childResult) {
					results.push_back(cr);
				}
			}
		}

		return results;
	}

	template <typename Graph, typename Node>
	void dijkstraSearch(
		Graph& _graph, Node _start, Node _end,
		std::unordered_map<Node, Node>& _cameFrom,
		std::unordered_map<Node, float>& _costSoFar) {

		PriorityQueue<Node, float> frontier;
		frontier.put(_start, 0.0f);

		_cameFrom[_start] = _start;
		_costSoFar[_start] = 0.0f;

		while (!frontier.empty()) {
			Node current = frontier.get();
			if (current == _end) {
				break;
			}

			for (Node next : _graph.neighbours(current)) {
				float newCost = _costSoFar[current] + _graph.cost(current, next);
				if (_costSoFar.count(next) == 0 ||
					newCost < _costSoFar[next]) {
					_costSoFar[next] = newCost;
					_cameFrom[next] = current;
					frontier.put(next, newCost);
				}
			}
		}
	}

	template <typename Graph, typename Node>
	void aStarSearch(
		Graph& _graph, Node _start, Node _end,
		std::unordered_map<Node, Node>& _cameFrom,
		std::unordered_map<Node, float>& _costSoFar) {

		PriorityQueue<Node, float> frontier;
		frontier.put(_start, 0.0f);

		_cameFrom[_start] = _start;
		_costSoFar[_start] = 0.0f;

		while (!frontier.empty()) {
			Node current = frontier.get();
			if (current == _end) {
				break;
			}

			for (Node next : _graph.neighbours(current)) {
				auto nextCost = _graph.cost(current, next);
				if (nextCost == std::numeric_limits<float>::max())
				{
					continue;
				}
				float newCost = _costSoFar[current] + nextCost;
				if (_costSoFar.count(next) == 0 ||
					newCost < _costSoFar[next]) {
					_costSoFar[next] = newCost;
					frontier.put(next, newCost + _graph.heuristic(next, _end));
					_cameFrom[next] = current;
				}
			}
		}
	}


	template<typename Node>
	std::vector<Node> reconstruct_path(
		Node _start, Node _end,
		std::unordered_map<Node, Node> _cameFrom) {
		std::vector<Node> path;
		Node current = _end;
		while (current != _start) {
			path.push_back(current);
			auto prevCurr = current;
			current = _cameFrom[current];
			if (current == prevCurr)
			{
				return{};
			}
		}
		path.push_back(_start);
		std::reverse(path.begin(), path.end());
		return path;
	}

}

namespace core {

	class EdgeNetwork {
	public:
		void addEdge(const std::string& _a, const std::string& _b);
		void addEdge(const std::string& _a, const std::string& _b, float _weight);
		std::vector<std::string> getShortestPath(const std::string& _start, const std::string& _end);
		std::vector<std::pair<std::string, std::pair<unsigned, float>>> performDepthFirstSearch(const std::string& _start, const std::string& _end);
		std::vector<std::pair<std::string, std::pair<unsigned, float>>> performBreadthFirstSearch(const std::string& _start, const std::string& _end);
		unsigned performDijkstraSearch(const std::string& _start, const std::string& _end);
		unsigned performAStarSearch(const std::string& _start, const std::string& _end);

		std::pair<std::vector<std::string>, float> getShortestPathVisitingAll();
		std::pair<std::vector<std::string>, float> getShortestPathVisitingAll(const std::string& _start);
		std::pair<std::vector<std::string>, float> getShortestPathVisitingAll(const std::string& _start, float _currentShortest);

		std::pair<std::vector<std::string>, float> getShortestPathVisitingAllReturningToStart();
		std::pair<std::vector<std::string>, float> getShortestPathVisitingAllReturningToStart(const std::string& _start);
		std::pair<std::vector<std::string>, float> getShortestPathVisitingAllReturningToStart(const std::string& _start, float _currentShortest);

		std::pair<std::vector<std::string>, float> getLongestPathVisitingAll();
		std::pair<std::vector<std::string>, float> getLongestPathVisitingAll(const std::string& _start);
		std::pair<std::vector<std::string>, float> getLongestPathVisitingAll(const std::string& _start, float _currentShortest);

		std::pair<std::vector<std::string>, float> getLongestPathVisitingAllReturningToStart();
		std::pair<std::vector<std::string>, float> getLongestPathVisitingAllReturningToStart(const std::string& _start);
		std::pair<std::vector<std::string>, float> getLongestPathVisitingAllReturningToStart(const std::string& _start, float _currentShortest);

		std::unordered_set<std::string> getNodes();

	private:
		internal::EdgeGraph sg{};
	};

	template <typename Cell>
	class CartesianNetwork {
	public:
		std::vector<Vector2i> performAStarSearch(const Vector2i& _start, const Vector2i& _end) {
			std::unordered_map<Vector2i, Vector2i> origins;
			std::unordered_map<Vector2i, float> costs;
			internal::aStarSearch<internal::CartesianGraph<Cell>, Vector2i>(cg, _start, _end, origins, costs);
			return internal::reconstruct_path(_start, _end, origins);			
		}

		std::vector<std::vector<Cell>>& getCells() { return cg.cells; }

		internal::CartesianGraph<Cell> cg{};
	};


}

#endif // INCLUDED_ADVENT_OF_CODE_CORE_PATHFINDING_HPP_