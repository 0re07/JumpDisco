#pragma once
class Vector2D
{
public:
	Vector2D();
	Vector2D(int x, int y);
	~Vector2D();
	int x;
	int y;

	//������Z�q
	Vector2D& operator=(const Vector2D& vec);

	//�Y�������Z�q
	int& operator[](int j);

	//�P�����Z�q
	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);
	Vector2D& operator%=(const Vector2D& vec);
	Vector2D operator+()const;
	Vector2D operator-()const;

	//�񍀉��Z�q
	Vector2D operator+(const Vector2D& vec);
	Vector2D operator-(const Vector2D& vec);
	Vector2D operator*(const Vector2D& vec);
	//Vector2D operator/(const Vector2D& vec);
	//Vector2D operator%(const Vector2D& vec);

	//��r���Z�q
	bool operator==(const Vector2D& vec)const;
	bool operator!=(const Vector2D& vec)const;
	bool operator<(const Vector2D& vec)const;
	bool operator<=(const Vector2D& vec)const;
	bool operator>(const Vector2D& vec)const;
	bool operator>=(const Vector2D& vec)const;

	//�����𐳋K������
	//void Normalize();

	Vector2D operator+(const Vector2D& v)const;
	Vector2D operator*(float scale);
	Vector2D Normalized() const;		//���K���ς݂̃x�N�g����Ԃ�
};

//�����̐��⏇�ԂŔ��f���Ă���̂ŁA���Ԃ␔���Ⴄ�ƃG���[���N����
//�����^
Vector2D operator*(const Vector2D vec,const int num);
Vector2D operator*(const int num, const Vector2D vec);

//�����_����
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
//	float Length() const;			//�x�N�g���̑傫����Ԃ�
//	Vector2 Normalized() const;		//���K���ς݂̃x�N�g����Ԃ�
//};

struct Circle
{
	Vector2D pos;	//���S
	float radius;	//���a
};

