#include "Vector2D.h"

Vector2D::Vector2D(double _x, double _y) : x_(_x), y_(_y)
{

}

Vector2D::~Vector2D()
{

}

double Vector2D::magnitude() const
{
	return std::sqrt(x_ * x_ + y_ * y_);
}

Vector2D Vector2D::normalize()
{
	double m = 1 / magnitude();
	return(Vector2D(x_ * m, y_ * m));
}

void Vector2D::rotate(double degrees)
{
	degrees = std::fmod(degrees, 360);
	if (degrees > 180) degrees -= 360;
	else if (degrees <= -180) degrees += 360;

	double _x = x_; double _y = y_;
	double a = degrees * PI / 180;
	x_ = std::cos(a) * _x - std::sin(a) * _y;
	y_ = std::sin(a) * _x + std::cos(a) * _y;
}

Vector2D Vector2D::operator+(const Vector2D& other)
{
	return Vector2D(x_ + other.x_, y_ + other.y_);
}

Vector2D Vector2D::operator-(const Vector2D& other)
{
	return Vector2D(x_ - other.x_, y_ - other.y_);
}

Vector2D Vector2D::operator*(const double& scalar)
{
	return Vector2D(x_ * scalar, y_ * scalar);
}

double Vector2D::operator*(const Vector2D& other)
{
	return x_ * other.x_ + y_ * other.y_;
}