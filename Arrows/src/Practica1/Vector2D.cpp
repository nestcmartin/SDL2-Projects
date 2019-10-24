#include "Vector2D.h"

Vector2D::Vector2D(double _x, double _y) : x(_x), y(_y)
{

}

Vector2D::~Vector2D()
{

}

double Vector2D::magnitude() const
{
	return std::sqrt(x * x + y * y);
}

Vector2D Vector2D::normalize()
{
	double m = 1 / magnitude();
	return(Vector2D(x * m, y * m));
}

void Vector2D::rotate(double degrees)
{
	degrees = std::fmod(degrees, 360);
	if (degrees > 180) degrees -= 360;
	else if (degrees <= -180) degrees += 360;

	double _x = x; double _y = y;
	double a = degrees * PI / 180;
	x = std::cos(a) * _x - std::sin(a) * _y;
	y = std::sin(a) * _x + std::cos(a) * _y;
}

Vector2D Vector2D::operator+(const Vector2D& other)
{
	return Vector2D(x + other.x, y + other.y);
}

Vector2D Vector2D::operator-(const Vector2D& other)
{
	return Vector2D(x - other.x, y - other.y);
}

Vector2D Vector2D::operator*(const double& scalar)
{
	return Vector2D(x * scalar, y * scalar);
}

double Vector2D::operator*(const Vector2D& other)
{
	return x * other.x + y * other.y;
}