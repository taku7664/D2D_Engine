#pragma once

class Vector2 {

public:

	float x = 0.f;
	float y = 0.f;

	//생성자
	Vector2() : x(0.f), y(0.f) {}
	// 오버로딩된 생성자
	Vector2(float _x, float _y = 0.f, float _z = 0.f) : x(_x), y(_y){}
	Vector2(int _x, int _y = 0, int _z = 0) : x((float)_x), y((float)_y) {}
	Vector2(long _x, long _y = 0, long _z = 0) : x((float)_x), y((float)_y) {}

	static const Vector2 Zero;
	static const Vector2 One;
	static const Vector2 Left;
	static const Vector2 Right;
	static const Vector2 Up;
	static const Vector2 Down;

	// 벡터의 크기 계산
	float Magnitude()
	{
		return (float)sqrt(x * x + y * y);
	}
	// 벡터의 정규화
	Vector2 Normalize()
	{
		Vector2 normal;
		float magnitude = this->Magnitude();
		normal.x = x / magnitude;
		normal.y = y / magnitude;
		return normal;
	}
	// 두 벡터의 내적 계산
	float DotProduct(const Vector2& _val)
	{
		return x * _val.x + y * _val.y;
	}
	// 두 벡터의 외적 계산
	float CrossProduct(const Vector2& _val)
	{
		return x * _val.y - y * _val.x;
	}

	// operator연산자
	Vector2& operator+=(const Vector2& _val)
	{
		x += _val.x;
		y += _val.y;
		return *this;
	}
	Vector2& operator+=(const float _val)
	{
		x += _val;
		y += _val;
		return *this;
	}

	Vector2& operator-=(const Vector2& _val)
	{
		x -= _val.x;
		y -= _val.y;
		return *this;
	}
	Vector2& operator-=(const float _val)
	{
		x -= _val;
		y -= _val;
		return *this;
	}
	Vector2& operator*=(const float _val)
	{
		x *= _val;
		y *= _val;
		return *this;
	}
	Vector2& operator*=(const Vector2& _val)
	{
		x *= _val.x;
		y *= _val.y;
		return *this;
	}
	Vector2& operator/=(const float _val)
	{
		x /= _val;
		y /= _val;
		return *this;
	}
	Vector2& operator/=(const Vector2& _val)
	{
		x /= _val.x;
		y /= _val.y;
		return *this;
	}
	Vector2 operator+(const Vector2& _val)
	{
		return Vector2(x + _val.x, y + _val.y);
	}

	Vector2 operator-(const Vector2& _val)
	{
		return Vector2(x - _val.x, y - _val.y);
	}

	Vector2 operator*(const Vector2& _val)
	{
		return Vector2(x * _val.x, y * _val.y);
	}
	Vector2 operator*(const float _val)
	{
		return Vector2(x * _val, y * _val);
	}
	Vector2 operator/(const Vector2& _val)
	{
		return Vector2(x / _val.x, y / _val.y);
	}
	Vector2 operator/(const float _val)
	{
		return Vector2(x / _val, y / _val);
	}
	Vector2& operator=(const Vector2& _val)
	{
		x = _val.x;
		y = _val.y;
		return *this;
	}
	bool operator==(const Vector2& _val)
	{
		return (x == _val.x && y == _val.y);
	}

};