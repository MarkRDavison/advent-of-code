#ifndef INCLUDED_ADVENT_OF_CODE_CORE_RECT_HPP_
#define INCLUDED_ADVENT_OF_CODE_CORE_RECT_HPP_

#include <Core/Vector2.hpp>

template <typename T>
class Rect
{
public:
    Rect(void);
    Rect(T _left, T _bot, T _width, T _height);
    Rect(const Vector2<T>& _position, const Vector2<T>& _size);
    template <typename U>
    explicit Rect(const Rect<U>& _rect);

    bool contains(T _x, T _y);
    bool contains(const Vector2<T>& _position);

    bool intersects(const Rect<T>& _rect, Rect<T>& _intersection = Rect<T>());

    void expandToContain(const Rect<T>& _rect);

    T left;
    T bot;
    T width;
    T height;
};

template <typename T>
bool operator ==(const Rect<T>& _left, const Rect<T>& _right);

template <typename T>
bool operator !=(const Rect<T>& _left, const Rect<T>& _right);

#include "Rect.inl"

typedef Rect<int> IntRect;
typedef Rect<float> FloatRect;

#endif // INCLUDED_ADVENT_OF_CODE_CORE_RECT_HPP_