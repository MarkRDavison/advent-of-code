#ifndef INCLUDED_ADVENT_OF_CODE_CORE_ORIENATION_HPP_
#define INCLUDED_ADVENT_OF_CODE_CORE_ORIENATION_HPP_

#include <Core/Vector2.hpp>
#include <string>

namespace core {

	enum class Orientation {
		Up,
		Down,
		Left, 
		Right,
		None
	};

	class OrientationHelper {
	public:
		OrientationHelper() = delete;
		~OrientationHelper() = delete;

		static std::string toString(Orientation _orientation) {
			switch (_orientation) {
			case Orientation::Up:
				return "Up";
			case Orientation::Down:
				return "Down";
			case Orientation::Left:
				return "Left";
			case Orientation::Right:
				return "Right";
			default:
				return "";
			}
		}

		static Vector2i toDirection(Orientation _orientation) {
			switch (_orientation) {
			case Orientation::Up:
				return Vector2i{ 0, +1 };
			case Orientation::Down:
				return Vector2i{ 0, -1 };
			case Orientation::Right:
				return Vector2i{ +1, 0 };
			case Orientation::Left:
				return Vector2i{ -1, 0 };
			default:
				return Vector2i{ 0, 0 };
			}
		}
		static Orientation reverse(Orientation _direction) {
			switch (_direction) {
			case Orientation::Up:
				return Orientation::Down;
			case Orientation::Down:
				return Orientation::Up;
			case Orientation::Left:
				return Orientation::Right;
			case Orientation::Right:
				return Orientation::Left;
			default:
				return Orientation::None;
			}
		}

		static Orientation turn(Orientation _direction, Orientation _turnDirection) {
			if (_turnDirection == Orientation::Up ||
				_turnDirection == Orientation::Down ||
				_turnDirection == Orientation::None ||
				_direction == Orientation::None) {
				return _direction;
			}

			if (_turnDirection == Orientation::Left) {
				switch (_direction) {
				case Orientation::Up:
					return Orientation::Left;
				case Orientation::Down:
					return Orientation::Right;
				case Orientation::Right:
					return Orientation::Up;
				case Orientation::Left:
					return Orientation::Down;
				}
			} else {
				switch (_direction) {
				case Orientation::Up:
					return Orientation::Right;
				case Orientation::Down:
					return Orientation::Left;
				case Orientation::Right:
					return Orientation::Down;
				case Orientation::Left:
					return Orientation::Up;
				}
			}

			return Orientation::None;
		}
	};

}

#endif // INCLUDED_ADVENT_OF_CODE_CORE_ORIENATION_HPP_