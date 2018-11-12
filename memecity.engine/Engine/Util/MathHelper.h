#ifndef _MATH_HELPER_H
#define _MATH_HELPER_H
#include <cmath>

#define PI 3.14159265
#define  DEG_TO_RAD PI / 180.0f

struct Vector2
{
	float x;
	float y;

	Vector2(float _x = 0.0f, float _y = 0.0f)
		: x(_x), y(_y) {}

	float MagnitudeSqr() const
	{
		return x * x + y * y;
	}

	float Magnitude() const
	{
		return float(sqrt(x * x + y * y));
	}

	Vector2 Normalized() const
	{
		const float mag = Magnitude();

		return { x / mag, y / mag };
	}

	Vector2& operator += (const Vector2& rhs)
	{
		x += rhs.x;
		y += rhs.y;

		return *this;
	}

	Vector2& operator -= (const Vector2& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;

		return *this;
	}
};

inline Vector2 operator +(const Vector2& lhs, const Vector2& rhs)
{
	return { lhs.x + rhs.x, lhs.y + rhs.y };
}

inline Vector2 operator -(const Vector2& lhs, const Vector2& rhs)
{
	return{ lhs.x - rhs.x, lhs.y - rhs.y };
}

inline Vector2 operator *(const Vector2& lhs, const float& rhs)
{
	return{ lhs.x * rhs, lhs.y * rhs };
}

inline Vector2 RotateVector(Vector2& vec, float angle)
{
	const float radAngle = float(angle * DEG_TO_RAD);
	return{ float(vec.x * cos(radAngle) - vec.y * sin(radAngle)), float(vec.x * sin(radAngle) + vec.y * cos(radAngle)) };
}

#endif
