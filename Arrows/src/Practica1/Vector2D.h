#ifndef __VECTOR_2D_H__
#define __VECTOR_2D_H__

#include <cmath>
#include <iostream>

const double PI = 3.14159265358979323846;

class Vector2D
{
private:
	double x;
	double y;

public:
	Vector2D(double _x = 0.0, double _y = 0.0);
	~Vector2D();

	inline double getX() const { return x; }
	inline double getY() const { return y; }
	inline void setX(double _x) { x = _x; }
	inline void setY(double _y) { y = _y; }

	Vector2D normalize();
	double magnitude() const;
	void rotate(double degrees);

	Vector2D operator+(const Vector2D& other);
	Vector2D operator-(const Vector2D& other);
	Vector2D operator*(const double& scalar);
	double operator*(const Vector2D& other);

	friend std::ostream& operator<<(std::ostream& out, const Vector2D& v)
	{
		out << v.x << " " << v.y;
		return out;
	}

	friend std::istream& operator>>(std::istream& in, Vector2D& v)
	{
		in >> v.x >> v.y;
		return in;
	}
};

typedef Vector2D Point2D;

#endif // !__VECTOR_2D_H__
