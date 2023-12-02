#include <2018/Day13Puzzle.hpp>
#include <Core/StringExtensions.hpp>
#include <unordered_map>
#include <unordered_set>
#include <Core/Vector2.hpp>
#include <Core/Region.hpp>
#include <Core/Orientation.hpp>
#include <stdexcept>
#include <algorithm>

namespace TwentyEighteen {
	
	Day13Puzzle::Day13Puzzle() :
		core::PuzzleBase("Mine Cart Madness", 2018, 13) {

	}
	Day13Puzzle::~Day13Puzzle() {

	}

	struct Cart
	{
		Vector2i position;
		Vector2i direction;
		int id{ 0 };
		int turn{ 0 };
		bool collided{ false };
	};

	void Day13Puzzle::initialise(const core::InitialisationInfo& _initialisationInfo) {
		setInputLines(StringExtensions::splitStringByDelimeter(StringExtensions::loadFileToString(_initialisationInfo.parameters[0]), "\n"));
	}

	void Day13Puzzle::setInputLines(const std::vector<std::string>& _inputLines) {
		m_InputLines = std::vector<std::string>(_inputLines);
	}

	char getCartFromDirection(Vector2i dir)
	{
		if (dir == Vector2i{ 0, -1 })
		{
			return '^';
		}
		if (dir == Vector2i{ 0, +1 })
		{
			return 'v';
		}
		if (dir == Vector2i{ -1, 0 })
		{
			return '<';
		}
		if (dir == Vector2i{ +1, 0 })
		{
			return '>';
		}

		throw std::runtime_error("Invalid cart direction");
	}

	Vector2i turnCart(core::Orientation turnDir, Vector2i dir)
	{
		if (dir == Vector2i{ -1, 0 })
		{
			if (turnDir == core::Orientation::Left)
			{
				return Vector2i{ 0, +1 };
			}
			if (turnDir == core::Orientation::Right)
			{
				return Vector2i{ 0, -1 };
			}
		}
		if (dir == Vector2i{ +1, 0 })
		{
			if (turnDir == core::Orientation::Left)
			{
				return Vector2i{ 0, -1 };
			}
			if (turnDir == core::Orientation::Right)
			{
				return Vector2i{ 0, +1 };
			}
		}
		if (dir == Vector2i{ 0, -1 })
		{
			if (turnDir == core::Orientation::Left)
			{
				return Vector2i{ -1, 0 };
			}
			if (turnDir == core::Orientation::Right)
			{
				return Vector2i{ +1, 0 };
			}
		}
		if (dir == Vector2i{ 0, +1 })
		{
			if (turnDir == core::Orientation::Left)
			{
				return Vector2i{ +1, 0 };
			}
			if (turnDir == core::Orientation::Right)
			{
				return Vector2i{ -1, 0 };
			}
		}

		throw std::runtime_error("INVALID TURN DIR");
	}

	std::unordered_set<Vector2i, Vector2_Hash_Fxn<int>> processTick(core::Region<char>& tracks, std::vector<Cart>& carts)
	{
		std::unordered_set<Vector2i, Vector2_Hash_Fxn<int>> collisions;
		std::unordered_map<Vector2i, int, Vector2_Hash_Fxn<int>> locations;

		for (auto& c : carts)
		{
			if (c.collided) { continue; }
			const auto cart = getCartFromDirection(c.direction);
			const auto next = c.position + c.direction;

			const auto nextRailChar = tracks.getCell(next.x, next.y);

			c.position += c.direction;

			for (auto& otherCart : carts)
			{
				if (otherCart.id != c.id)
				{
					if (otherCart.position == c.position)
					{
						otherCart.collided = true;
						c.collided = true;
						collisions.emplace(c.position);
					}
				}
			}

			if (nextRailChar == '/')
			{
				if (cart == '>')
				{
					c.direction = Vector2i{ 0,-1 };
				}
				else if (cart == '<')
				{
					c.direction = Vector2i{ 0,+1 };
				}
				else if (cart == '^')
				{
					c.direction = Vector2i{ +1,0 };
				}
				else if (cart == 'v')
				{
					c.direction = Vector2i{ -1,0 };
				}
			}
			else if (nextRailChar == '\\')
			{
				if (cart == '>')
				{
					c.direction = Vector2i{ 0,+1 };
				}
				else if (cart == '<')
				{
					c.direction = Vector2i{ 0,-1 };
				}
				else if (cart == '^')
				{
					c.direction = Vector2i{ -1,0 };
				}
				else if (cart == 'v')
				{
					c.direction = Vector2i{ +1,0 };
				}
			}
			else if (nextRailChar == '+')
			{
				if (c.turn == 0)
				{
					// turn left
					c.direction = turnCart(core::Orientation::Left, c.direction);
				}
				else if (c.turn == 1)
				{
					// go straight
				}
				else if (c.turn == 2)
				{
					// turn right
					c.direction = turnCart(core::Orientation::Right, c.direction);
				}

				c.turn = (c.turn + 1) % 3;
			}

			locations[c.position]++;
		}

		carts.erase(
			std::remove_if(
				carts.begin(),
				carts.end(),
				[](const Cart& cart) -> bool
				{
					return cart.collided;
				}),
			carts.end());

		return collisions;
	}
	void dumpTracks(core::Region<char>& tracks, const std::vector<Cart>& carts)
	{
		std::vector<std::string> output;

		for (int y = 0; y < tracks.maxY + 1; ++y)
		{
			output.emplace_back(std::string(tracks.maxX + 1, ' '));
			for (int x = 0; x < tracks.maxX + 1; ++x)
			{
				output[y][x] = tracks.getCell(x, y);
			}
		}

		for (const auto& c : carts)
		{
			output[c.position.y][c.position.x] = getCartFromDirection(c.direction);
		}


		for (const auto& s : output)
		{
			std::cout << s << std::endl;
		}
	}

	std::pair<std::string, std::string> Day13Puzzle::fastSolve() {
		const std::unordered_map<char, Vector2i> minecartDir {
			{'^', {0,-1}}, {'v', {0,+1}}, {'<', {-1,0}}, {'>', {+1,0}}
		};
		const std::unordered_map<Vector2i, char, Vector2_Hash_Fxn<int>> dirMinecart {
			{{0,-1}, '^'}, {{0,+1}, 'v'}, {{-1,0}, '<'}, {{+1,0}, '>'}
		};
		const std::unordered_map<char, char> minecartTrackChar {
			{'^', '|'}, {'v', '|'}, {'<', '-'}, {'>', '-'}
		};

		std::vector<Cart> carts;
		core::Region<char> tracks;
		for (int y = 0; y < m_InputLines.size(); ++y)
		{
			for (int x = 0; x < m_InputLines[y].size(); ++x)
			{
				char c = m_InputLines[y][x];
				if (c == '^' || c == 'v' || c == '<' || c == '>')
				{
					auto& cart = carts.emplace_back();
					cart.position = Vector2i{ x,y };
					cart.direction = minecartDir.at(c);
					cart.id = carts.size();
					c = minecartTrackChar.at(c);
				}
				tracks.getCell(x, y) = c;
			}
		}


		std::string part1;
		std::string part2;
		if (getVerbose())
		{
			std::cout << "Initial position." << std::endl;
			dumpTracks(tracks, carts);
		}

		int count = 0;
		while (part2.empty())
		{
			count++;
			std::sort(
				carts.begin(),
				carts.end(),
				[](const Cart& lhs, Cart& rhs) -> int
				{

					if (lhs.position.y == rhs.position.y)
					{
						return lhs.position.x < rhs.position.x;
					}
					return lhs.position.y < rhs.position.y;
				});
			auto collisions = processTick(tracks, carts);
			if (!collisions.empty())
			{
				if (part1.empty())
				{
					part1 = std::to_string(collisions.begin()->x) + "," + std::to_string(collisions.begin()->y);
				}
			}

			if (part2.empty() && carts.size() == 1)
			{
				part2 = std::to_string(carts[0].position.x) + "," + std::to_string(carts[0].position.y);
			}

			if (carts.empty())
			{
				break;
			}

			if (getVerbose())
			{
				std::cout << "============================" << std::endl;
				std::cout << "After " << count << " ticks." << std::endl;
				dumpTracks(tracks, carts);
			}
		}
		return { part1, part2 };
	}
}
