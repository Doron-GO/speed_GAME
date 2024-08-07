#pragma once
#include <cmath>

//template <class T>class クラス名
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

	//代入演算子
	Vector2DTemp& operator=(const Vector2DTemp& vec);

	//添え字演算子
	T& operator[](int j);

	//単項演算子

	Vector2DTemp& operator+=(const Vector2DTemp& vec);
	Vector2DTemp& operator-=(const Vector2DTemp& vec);
	Vector2DTemp& operator*=(const Vector2DTemp& vec);
	Vector2DTemp& operator/=(const Vector2DTemp& vec);
	Vector2DTemp& operator%=(const Vector2DTemp& vec);
	Vector2DTemp operator+()const;
	Vector2DTemp operator-()const;

	//二項演算子
	Vector2DTemp operator+(const Vector2DTemp& vec);
	Vector2DTemp operator-(const Vector2DTemp& vec);
	Vector2DTemp operator*(const Vector2DTemp& vec);
	Vector2DTemp operator%(const Vector2DTemp& vec);

	//比較演算子
	bool operator==(const Vector2DTemp& vec)const;
	bool operator!=(const Vector2DTemp& vec)const;
	bool operator<(const Vector2DTemp& vec)const;
	bool operator<=(const Vector2DTemp& vec)const;
	bool operator>(const Vector2DTemp& vec)const;
	bool operator>=(const Vector2DTemp& vec)const;

};

//引数の数や順番で判断しているので、順番や数が違うとエラーが起きる
//整数型

//
template <class T>
Vector2DTemp<T> operator*(const Vector2DTemp<T> vec, const int num);
template <class T>
Vector2DTemp < T> operator*(const int num, const Vector2DTemp<T> vec);

//小数点も可
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

template <class T>
Vector2DTemp<T>::Vector2DTemp()
{
	x = 0;
	y = 0;
}
template <class T>
Vector2DTemp<T>::Vector2DTemp(T x, T y)
{
	Vector2DTemp::x = x;
	Vector2DTemp::y = y;
}

template <class T>
Vector2DTemp<T>::~Vector2DTemp()
{
}

template <class T>
constexpr T Vector2DTemp<T>::Magnitude(void) const
{
	return static_cast<T>(sqrt(SqMagnitude()));

}

template<class T>
constexpr T Vector2DTemp<T>::SqMagnitude(void) const
{
	return x * x + y * y ;
}

template<class T>
inline void Vector2DTemp<T>::Normalize(void)
{
	T mag = Magnitude();
	x /= mag;
	y /= mag;

}

template<class T>
inline constexpr Vector2DTemp<T> Vector2DTemp<T>::Normalized(void) const
{
	T mag = Magnitude();
	return Vector2DTemp(x / mag, y / mag);
}

template<class T>
inline constexpr T Vector2DTemp<T>::Dot(const Vector2DTemp& vec) const
{
	return x * vec.x + y * vec.y ;
}

template<class T>
inline constexpr Vector2DTemp<T> Vector2DTemp<T>::Cross(const Vector2DTemp& vec) const
{
	return Vector2DTemp(x* vec.y - y * vec.x);
}

template<class T>
inline constexpr T Vector2DTemp<T>::distance(const Vector2DTemp& vec) const
{
	return 	Vector2DTemp(x - vec.x, y - vec.y).Magnitude();

}


//代入演算子

template <class T>Vector2DTemp<T>& Vector2DTemp<T>::operator=(const Vector2DTemp<T>& vec)
{
	x = vec.x;
	y = vec.y;

	return *this;

}

//添え字演算子
template <class T>
T& Vector2DTemp<T>::operator[](int j)
{
	switch (j)
	{
	case 0:
		return x;
		//break;
	case 1:
		return y;
		//break;
	default:
		return x;
		//break;
	}
}

//単項演算子

template <class T>
Vector2DTemp<T>& Vector2DTemp<T>::operator+=(const Vector2DTemp<T>& vec)
{
	x += vec.x;
	y += vec.y;

	return *this;
}

template <class T>
Vector2DTemp<T>& Vector2DTemp<T>::operator-=(const Vector2DTemp<T>& vec)
{
	x -= vec.x;
	y -= vec.y;

	return *this;
}
template <class T>
Vector2DTemp<T>& Vector2DTemp<T>::operator*=(const Vector2DTemp<T>& vec)
{
	x *= vec.x;
	y *= vec.y;

	return *this;
}
template <class T>
Vector2DTemp<T>& Vector2DTemp<T>::operator/=(const Vector2DTemp<T>& vec)
{
	//ガード処理
	if (vec.x)
	{
		x /= vec.x;
	}
	else
	{
		x = 0;
	}
	if (vec.y)
	{
		y /= vec.y;
	}
	else
	{
		y = 0;
	}


	return *this;
}
template <class T>
Vector2DTemp<T>& Vector2DTemp<T>::operator%=(const Vector2DTemp<T>& vec)
{
	//ガード処理
	if (vec.x)
	{
		x = static_cast<int>(x) % static_cast<int>(vec.x);
	}
	else
	{
		x = 0;
	}
	if (vec.y)
	{
		y = static_cast<int>(y) % static_cast<int>(vec.y);
	}
	else
	{
		y = 0;
	}
	

	return *this;
}
template <class T>
Vector2DTemp<T> Vector2DTemp<T>::operator+() const
{
	return *this;
}
template <class T>
Vector2DTemp<T> Vector2DTemp<T>::operator-() const
{

	return{ -x,-y };
}

//二項演算子
template <class T>
Vector2DTemp<T> Vector2DTemp<T>::operator+(const Vector2DTemp<T>& vec)
{
	//Vector2D val;
	//val.x = x + vec.x;
	//val.y = y + vec.y;
	//return val;
	return { x + vec.x,y + vec.y };
}
template <class T>
Vector2DTemp<T> Vector2DTemp<T>::operator-(const Vector2DTemp<T>& vec)
{
	return { x - vec.x,y - vec.y };
}
template <class T>
Vector2DTemp<T> Vector2DTemp<T>::operator*(const Vector2DTemp<T>& vec)
{
	return { x * vec.x,y * vec.y };
}

//比較演算子
template <class T>
bool Vector2DTemp<T>::operator==(const Vector2DTemp<T>& vec) const
{
	//if (x == vec.x && y == vec.y)
	//{
	//	return true;
	//}
	//return false;
	return(x == vec.x && y == vec.y);
}
template <class T>
bool Vector2DTemp<T>::operator!=(const Vector2DTemp<T>& vec) const
{
	return(x != vec.x && y != vec.y);
}
template <class T>
bool Vector2DTemp<T>::operator<(const Vector2DTemp<T>& vec) const
{
	return(x < vec.x && y < vec.y);
}
template <class T>
bool Vector2DTemp<T>::operator<=(const Vector2DTemp<T>& vec) const
{
	return(x <= vec.x && y <= vec.y);
}
template <class T>
bool Vector2DTemp<T>::operator>(const Vector2DTemp<T>& vec) const
{
	return(x > vec.x && y > vec.y);
}
template <class T>
bool Vector2DTemp<T>::operator>=(const Vector2DTemp<T>& vec) const
{
	return(x >= vec.x && y >= vec.y);
}
template <class T>
Vector2DTemp<T> operator*(const Vector2DTemp<T>& vec1, const Vector2DTemp<T>& vec2)
{
	return {vec1.x*vec2.x,vec1.y*vec2.y};
}

//整数型
template <class T>
Vector2DTemp<T> operator*(const Vector2DTemp<T> vec, const int num)
{
	return{ vec.x * num,vec.y * num };
}
template <class T>
Vector2DTemp<T> operator*(const int num, const Vector2DTemp<T> vec)
{
	return{ vec.x * num,vec.y * num };
}


//小数点も可
template <class T>
Vector2DTemp<T> operator*(const Vector2DTemp<T> vec, const float num)
{
	return{vec.x * num,vec.y * num };
}
template <class T>
Vector2DTemp<T> operator*(const float num, const Vector2DTemp<T> vec)
{
	return{vec.x * num,vec.y * num };
}
template <class T>
Vector2DTemp<T> operator/(const Vector2DTemp<T> vec, const int num)
{
	return{ vec.x / num,vec.y / num };
}
template <class T>
Vector2DTemp<T> operator/(const Vector2DTemp<T> vec1, Vector2DTemp<T> vec2)
{
	Vector2DTemp<T> val;
	//ガード処理
	if (vec2.x)
	{
		val.x = vec1.x / vec2.x;
	}
	else
	{
		val.x = 0;
	}
	if (vec2.y)
	{
		val.y =vec1. y / vec2.y;
	}
	else
	{
		val.y = 0;
	}
	return val;
}
template <class T>
Vector2DTemp<T> operator%(const Vector2DTemp<T> vec1, Vector2DTemp<T> vec2)
{
	Vector2DTemp<T> val;
	//ガード処理
	if (vec2.x)
	{
		val.x = vec1.x % vec2.x;
	}
	else
	{
		val.x = 0;
	}
	if (vec2.y)
	{
		val.y = vec1.y % vec2.y;
	}
	else
	{
		val.y = 0;
	}
	return val;
}
