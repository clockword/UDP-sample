#pragma once
class Vector2
{
public:
	float x;
	float y;

public:
	Vector2();
	Vector2(float x, float y);
	Vector2(Vector2 begin, Vector2 end);
	virtual ~Vector2();

	Vector2& operator = (const Vector2 vec);
	Vector2& operator = (const float scalar);
	bool operator == (const Vector2& vec) const;
	bool operator != (const Vector2& vec) const;
	Vector2 operator + (const Vector2& vec) const;
	Vector2 operator - (const Vector2& vec) const;
	Vector2 operator * (const Vector2& vec) const;
	Vector2 operator * (const float scalar) const;
	Vector2 operator / (const Vector2& vec) const;
	Vector2 operator / (const float scalar) const;
	Vector2 operator - () const;
	Vector2& operator += (const Vector2& vec);
	Vector2& operator += (const float scalar);
	Vector2& operator -= (const Vector2& vec);
	Vector2& operator -= (const float scalar);
	Vector2& operator *= (const Vector2& vec);
	Vector2& operator *= (const float scalar);
	Vector2& operator /= (const Vector2& vec);
	Vector2& operator /= (const float scalar);

	float GetMagnitude();
	float GetSqrMagnitude();
	Vector2 GetNormalized();
	void Normalize();
	Vector2 GetReverse();

	static float Dot(Vector2 lhs, Vector2 rhs);
	static Vector2 Lerp(Vector2 a, Vector2 b, float t);
	static float Angle(Vector2 from, Vector2 to);
	static float Distance(Vector2 vec1, Vector2 vec2);
	static Vector2 Normalize(Vector2 begin, Vector2 end);
	static Vector2 Zero();
	static Vector2 Left();
	static Vector2 Right();
	static Vector2 Up();
	static Vector2 Down();
};

