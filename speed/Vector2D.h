#pragma once
//template <class T>class �N���X��
template <class T>class Vector2DTemp
{
public:
	Vector2DTemp();
	Vector2DTemp(T x, T y);
	~Vector2DTemp();
	T x;
	T y;
	constexpr T Magnitude(void)const;

	constexpr T SqMagnitude(void)const;

	void Normalize(void);
	constexpr Vector2DTemp Normalized(void)const;
	constexpr T Dot(const Vector2DTemp& vec)const;
	constexpr Vector2DTemp Cross(const Vector2DTemp& vec)const;
	constexpr T distance(const Vector2DTemp& vec)const;

	//������Z�q
	Vector2DTemp& operator=(const Vector2DTemp& vec);

	//�Y�������Z�q
	T& operator[](int j);

	//�P�����Z�q

	Vector2DTemp& operator+=(const Vector2DTemp& vec);
	Vector2DTemp& operator-=(const Vector2DTemp& vec);
	Vector2DTemp& operator*=(const Vector2DTemp& vec);
	Vector2DTemp& operator/=(const Vector2DTemp& vec);
	Vector2DTemp& operator%=(const Vector2DTemp& vec);
	Vector2DTemp operator+()const;
	Vector2DTemp operator-()const;

	//�񍀉��Z�q
	Vector2DTemp operator+(const Vector2DTemp& vec);
	Vector2DTemp operator-(const Vector2DTemp& vec);
	Vector2DTemp operator*(const Vector2DTemp& vec);
	//Vector2D operator/(const Vector2D& vec);
	Vector2DTemp operator%(const Vector2DTemp& vec);

	//��r���Z�q
	bool operator==(const Vector2DTemp& vec)const;
	bool operator!=(const Vector2DTemp& vec)const;
	bool operator<(const Vector2DTemp& vec)const;
	bool operator<=(const Vector2DTemp& vec)const;
	bool operator>(const Vector2DTemp& vec)const;
	bool operator>=(const Vector2DTemp& vec)const;




};

//�����̐��⏇�ԂŔ��f���Ă���̂ŁA���Ԃ␔���Ⴄ�ƃG���[���N����
//�����^

//
template <class T>
Vector2DTemp<T> operator*(const Vector2DTemp<T> vec,const int num);
template <class T>
Vector2DTemp < T> operator*(const int num, const Vector2DTemp<T> vec);

//�����_����
template <class T>
Vector2DTemp<T> operator*(const Vector2DTemp<T>& vec1, const Vector2DTemp<T>& vec2);
template <class T>
Vector2DTemp<T> operator*(const Vector2DTemp<T> vec, const float num);
template <class T>
Vector2DTemp<T> operator*(const float num, const Vector2DTemp<T> vec);

template <class T>
Vector2DTemp<T> operator/(const Vector2DTemp<T> vec, const int num);
template <class T>
Vector2DTemp<T> operator/(const Vector2DTemp<T> vec1, Vector2DTemp<T> vec2);

using Vector2D = Vector2DTemp<int>;
using Vector2DFloat = Vector2DTemp<float>;
using Vector2DDouble = Vector2DTemp<double>;

//details��Vrctoe2D.h��include����
#include"details/Vector2D.h"