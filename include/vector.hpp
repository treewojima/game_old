#ifndef __VECTOR_HPP__
#define __VECTOR_HPP__

//#include <Box2D/Common/b2Math.h>
#include <string>
#include <sstream>

#include "defines.hpp"

template <class T>
struct Vector2
{
    T x, y;

    Vector2(T x_ = 0, T y_ = 0) : x(x_), y(y_) {}
    Vector2(const Vector2 &v) : x(v.x), y(v.y) {}
    //Vector2(const b2Vec2 &v) : x(v.x), y(v.y) {}

    void set(T x_, T y_) { x = x_; y = y_; }
    void set(const Vector2 &v) { x = v.x; y = v.y; }
    //void set(const b2Vec2 &v) { x = v.x; y = v.y; }
    void setZero() { x = y = 0; }

    /*inline b2Vec2 tob2Vec2()
    {
        return b2Vec2(static_cast<float32>(x), static_cast<float32>(y));
    }*/

    std::string toString() const
    {
        std::ostringstream ss;
        ss << "Vector<Position: (" << x << ", " << y << ")>";
        return ss.str();
    }
};
typedef Vector2<int> Vector2i;
typedef Vector2<float> Vector2f;

#endif
