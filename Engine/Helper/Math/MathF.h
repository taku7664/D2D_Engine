#pragma once

struct
{
private:

	float _PI_D_180F = 0.0174533f;
	float _180F_D_Pi = 57.2958f;

public:

	const float PI = 3.14159265358979323846f;

	template <typename T>
	T Lerp(T start, T end, float t)
	{
		return start * (1 - t) + end * t;
	}

	template <typename T>
	T Clamp(T const _val, T const _min, T const _max)
	{
		return (_val > _max ? _max : (_val <= _min ? _min : _val));
	}

	float Degree2Radian(float _degree)
	{
		return _degree * _PI_D_180F;
	}

	float Radian2Degree(float _radian)
	{
		return _radian * _180F_D_Pi;
	}

	//https://ncanis.tistory.com/434
}MathF;