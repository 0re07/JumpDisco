#pragma once
class Vector2D
{
public:
	Vector2D();
	Vector2D(int x, int y);
	~Vector2D();
	int x;
	int y;

	//代入演算子
	Vector2D& operator=(const Vector2D& vec);

	//添え字演算子
	int& operator[](int j);

	//単項演算子
	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);
	Vector2D& operator%=(const Vector2D& vec);
	Vector2D operator+()const;
	Vector2D operator-()const;

	//二項演算子
	Vector2D operator+(const Vector2D& vec);
	Vector2D operator-(const Vector2D& vec);
	Vector2D operator*(const Vector2D& vec);
	//Vector2D operator/(const Vector2D& vec);
	//Vector2D operator%(const Vector2D& vec);

	//比較演算子
	bool operator==(const Vector2D& vec)const;
	bool operator!=(const Vector2D& vec)const;
	bool operator<(const Vector2D& vec)const;
	bool operator<=(const Vector2D& vec)const;
	bool operator>(const Vector2D& vec)const;
	bool operator>=(const Vector2D& vec)const;

	//自分を正規化する
	//void Normalize();

	Vector2D operator+(const Vector2D& v)const;
	Vector2D operator*(float scale);
	Vector2D Normalized() const;		//正規化済みのベクトルを返す
};

//引数の数や順番で判断しているので、順番や数が違うとエラーが起きる
//整数型
Vector2D operator*(const Vector2D vec,const int num);
Vector2D operator*(const int num, const Vector2D vec);

//小数点も可
Vector2D operator*(const Vector2D& vec1, const Vector2D& vec2);
//Vector2D operator*(const Vector2D vec, const float num);
Vector2D operator*(const float num, const Vector2D vec);


Vector2D operator/(const Vector2D vec, const int num);

Vector2D operator/(const Vector2D vec1, Vector2D vec2);
Vector2D operator%(const Vector2D vec1, Vector2D vec2);

bool operator>=(const Vector2D vec1, Vector2D vec2);

Vector2D operator-(const Vector2D lv, const Vector2D rv);

//struct Vector2 {
//	float x;
//	float y;
//	float Length() const;			//ベクトルの大きさを返す
//	Vector2 Normalized() const;		//正規化済みのベクトルを返す
//};

struct Circle
{
	Vector2D pos;	//中心
	float radius;	//半径
};

