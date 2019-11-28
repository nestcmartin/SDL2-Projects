#ifndef __VECTOR_2D_H__
#define __VECTOR_2D_H__

#include <cmath>
#include <iostream>

const double PI = 3.14159265358979323846;

class Vector2D
{
private:
	double x_;
	double y_;

public:
	Vector2D(double _x = 0.0, double _y = 0.0);
	~Vector2D();

	inline double getX() const { return x_; }
	inline double getY() const { return y_; }
	inline void setX(double _x) { x_ = _x; }
	inline void setY(double _y) { y_ = _y; }
	inline void set(double _x, double _y) { x_ = _x; y_ = _y; }

	Vector2D normalize();
	double magnitude() const;
	void rotate(double degrees);

	Vector2D operator+(const Vector2D& other);
	Vector2D operator-(const Vector2D& other);
	Vector2D operator*(const double& scalar);
	double operator*(const Vector2D& other);

	friend std::ostream& operator<<(std::ostream& out, const Vector2D& v)
	{
		out << v.x_ << " " << v.y_;
		return out;
	}

	friend std::istream& operator>>(std::istream& in, Vector2D& v)
	{
		in >> v.x_ >> v.y_;
		return in;
	}
};

typedef Vector2D Point2D;

#endif // !__VECTOR_2D_H__
