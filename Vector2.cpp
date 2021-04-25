#include "Vector2.h"
#include <cmath>

Vector2::Vector2()
{
	x = 0.0f;
	y = 0.0f;
}

Vector2::Vector2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2::Vector2(Vector2 begin, Vector2 end)
{
	Vector2 vec = end - begin;
	this->x = vec.x;
	this->y = vec.y;
}

Vector2::~Vector2()
{
}

Vector2& Vector2::operator=(const Vector2 vec)
{
	x = vec.x;
	y = vec.y;

	return *this;
}

Vector2& Vector2::operator=(const float scalar)
{
	x = scalar;
	y = scalar;

	return *this;
}

bool Vector2::operator==(const Vector2& vec) const
{
	return (x == vec.x && y == vec.y);
}

bool Vector2::operator!=(const Vector2& vec) const
{
	return (x != vec.x || y != vec.y);
}

Vector2 Vector2::operator+(const Vector2& vec) const
{
	Vector2 rVec;

	rVec.x = x + vec.x;
	rVec.y = y + vec.y;

	return rVec;
}

Vector2 Vector2::operator-(const Vector2& vec) const
{
	Vector2 rVec;

	rVec.x = x - vec.x;
	rVec.y = y - vec.y;

	return rVec;
}

Vector2 Vector2::operator*(const Vector2& vec) const
{
	Vector2 rVec;

	rVec.x = x * vec.x;
	rVec.y = y * vec.y;

	return rVec;
}

Vector2 Vector2::operator*(const float scalar) const
{
	Vector2 rVec;

	rVec.x = x * scalar;
	rVec.y = y * scalar;

	return rVec;
}

Vector2 Vector2::operator/(const Vector2& vec) const
{
	Vector2 rVec;

	rVec.x = x / vec.x;
	rVec.y = y / vec.y;

	return rVec;
}

Vector2 Vector2::operator/(const float scalar) const
{
	Vector2 rVec;
	float v = 1.0f / scalar;

	rVec.x = x * v;
	rVec.y = y * v;

	return rVec;
}

Vector2 Vector2::operator-() const
{
	Vector2 rVec;

	rVec.x = -x;
	rVec.y = -y;

	return rVec;
}

Vector2& Vector2::operator+=(const Vector2& vec)
{
	x += vec.x;
	y += vec.y;

	return *this;
}

Vector2& Vector2::operator+=(const float scalar)
{
	x += scalar;
	y += scalar;

	return *this;
}

Vector2& Vector2::operator-=(const Vector2& vec)
{
	x -= vec.x;
	y -= vec.y;

	return *this;
}

Vector2& Vector2::operator-=(const float scalar)
{
	x -= scalar;
	y -= scalar;

	return *this;
}

Vector2& Vector2::operator*=(const Vector2& vec)
{
	x *= vec.x;
	y *= vec.y;

	return *this;
}

Vector2& Vector2::operator*=(const float scalar)
{
	x *= scalar;
	y *= scalar;

	return *this;
}

Vector2& Vector2::operator/=(const Vector2& vec)
{
	x /= vec.x;
	y /= vec.y;

	return *this;
}

Vector2& Vector2::operator/=(const float scalar)
{
	float v = 1.0f / scalar;

	x *= v;
	y *= v;

	return *this;
}

float Vector2::GetMagnitude()
{
	return sqrtf(x * x + y * y);
}

float Vector2::GetSqrMagnitude()
{
	return x * x + y * y;
}

Vector2 Vector2::GetNormalized()
{
	Vector2 temp = *this;

	temp.Normalize();

	return temp;
}

void Vector2::Normalize()
{
	x /= GetMagnitude();
	y /= GetMagnitude();
}

Vector2 Vector2::GetReverse()
{
	return -(*this);
}

float Vector2::Dot(Vector2 lhs, Vector2 rhs)
{
	return lhs.x * rhs.x + lhs.y * rhs.y;
}

Vector2 Vector2::Lerp(Vector2 a, Vector2 b, float t)
{
	return a * (1.0f - t) + b * t;
}

float Vector2::Angle(Vector2 from, Vector2 to)
{
	return acosf(Dot(from, to) / from.GetMagnitude() / to.GetMagnitude());
}

float Vector2::Distance(Vector2 vec1, Vector2 vec2)
{
	return (vec1 - vec2).GetMagnitude();
}

Vector2 Vector2::Normalize(Vector2 begin, Vector2 end)
{
	return (end - begin).GetNormalized();
}

Vector2 Vector2::Zero()
{
	Vector2 temp(0.0f, 0.0f);

	return temp;
}
