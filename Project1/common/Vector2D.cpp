#include <math.h>
#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0;
	y = 0;
}

Vector2D::Vector2D(int x, int y)
{
	Vector2D::x = x;
	Vector2D::y = y;
}

Vector2D::~Vector2D()
{
}

//‘ã“ü‰‰Zq
Vector2D& Vector2D::operator=(const Vector2D& vec)
{
	x = vec.x;
	y = vec.y;

	return *this;

}

//“Y‚¦š‰‰Zq
int& Vector2D::operator[](int j)
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

//’P€‰‰Zq
Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	x += vec.x;
	y += vec.y;

	return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	x -= vec.x;
	y -= vec.y;

	return *this;
}

Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	x *= vec.x;
	y *= vec.y;

	return *this;
}

Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	//ƒK[ƒhˆ—
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

Vector2D& Vector2D::operator%=(const Vector2D& vec)
{
	//ƒK[ƒhˆ—
	if (vec.x)
	{
		x %= vec.x;
	}
	else
	{
		x = 0;
	}
	if (vec.y)
	{
		y %= vec.y;
	}
	else
	{
		y = 0;
	}
	

	return *this;
}

Vector2D Vector2D::operator+() const
{
	return *this;
}

Vector2D Vector2D::operator-() const
{
	return{ -x,-y };
}

//“ñ€‰‰Zq
Vector2D Vector2D::operator+(const Vector2D& vec)
{
	//Vector2D val;
	//val.x = x + vec.x;
	//val.y = y + vec.y;
	//return val;
	return { x + vec.x,y + vec.y };
}

Vector2D Vector2D::operator-(const Vector2D& vec)
{
	return { x - vec.x,y - vec.y };
}

Vector2D Vector2D::operator*(const Vector2D& vec)
{
	return { x * vec.x,y * vec.y };
}

//Vector2D Vector2D::operator/(const Vector2D& vec)
//{
//	Vector2D val;
//	//ƒK[ƒhˆ—
//	if (vec.x)
//	{
//		val.x = x / vec.x;
//	}
//	else
//	{
//		val.x = 0;
//	}
//	if (vec.y)
//	{
//		val.y = y / vec.y;
//	}
//	else
//	{
//		val.y = 0;
//	}
//
//	
//	return val;
//}

//Vector2D Vector2D::operator%(const Vector2D& vec)
//{
//	Vector2D val;
//	//ƒK[ƒhˆ—
//	if (vec.x)
//	{
//		val.x = x % vec.x;
//	}
//	else
//	{
//		val.x = 0;
//	}
//	if (vec.y)
//	{
//		val.y = y % vec.y;
//	}
//	else
//	{
//		val.y = 0;
//	}
//	return val;
//}

//”äŠr‰‰Zq
bool Vector2D::operator==(const Vector2D& vec) const
{
	//if (x == vec.x && y == vec.y)
	//{
	//	return true;
	//}
	//return false;
	return(x == vec.x && y == vec.y);
}

bool Vector2D::operator!=(const Vector2D& vec) const
{
	return(x != vec.x && y != vec.y);
}

bool Vector2D::operator<(const Vector2D& vec) const
{
	return(x < vec.x && y < vec.y);
}

bool Vector2D::operator<=(const Vector2D& vec) const
{
	return(x <= vec.x && y <= vec.y);
}

bool Vector2D::operator>(const Vector2D& vec) const
{
	return(x > vec.x && y > vec.y);
}

bool Vector2D::operator>=(const Vector2D& vec) const
{
	return(x >= vec.x && y >= vec.y);
}

Vector2D Vector2D::operator+(const Vector2D& v) const
{
	return Vector2D();
}

Vector2D Vector2D::operator*(float scale)
{
	return { static_cast<int>(x * scale) ,static_cast<int>(y * scale) };

}

Vector2D Vector2D::Normalized() const
{
	auto len = hypotf(x, y);
	return { static_cast<int>(x / len),static_cast<int>(y / len) };
}

//®”Œ^
Vector2D operator*(const Vector2D vec, const int num)
{
	return{ vec.x * num,vec.y * num };
}

Vector2D operator*(const int num, const Vector2D vec)
{
	return{ vec.x * num,vec.y * num };
}


Vector2D operator*(const Vector2D& vec1, const Vector2D& vec2)
{
	return{ vec1.x * vec2.x,vec1.y * vec2.y };
}

//¬”“_‚à‰Â
Vector2D operator*(const Vector2D vec, const float num)
{
	return{ static_cast<int>(vec.x * num),static_cast<int>(vec.y * num) };
}

Vector2D operator*(const float num, const Vector2D vec)
{
	return{ static_cast<int>(vec.x * num),static_cast<int>(vec.y * num) };
}

Vector2D operator/(const Vector2D vec, const int num)
{
	return{ vec.x / num,vec.y / num };
}

Vector2D operator/(const Vector2D vec1, Vector2D vec2)
{
	Vector2D val;
	//ƒK[ƒhˆ—
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
		val.y = vec1.y / vec2.y;
	}
	else
	{
		val.y = 0;
	}


	return val;
}

Vector2D operator%(const Vector2D vec1, Vector2D vec2)
{
	Vector2D val;
	//ƒK[ƒhˆ—
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

bool operator>=(const Vector2D vec1, Vector2D vec2)
{
	return(vec1.x >= vec2.x && vec1.y >= vec2.y);
}

Vector2D
operator-(const Vector2D lv, const Vector2D rv) {
	return { lv.x - rv.x,lv.y - rv.y };
}