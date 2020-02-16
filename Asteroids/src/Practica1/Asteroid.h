#ifndef __ASTEROID_H__
#define __ASTEROID_H__

#include "Vector2D.h"

class Asteroid
{
private:
	Vector2D position_;
	Vector2D velocity_;
	double width_;
	double height_;
	double rotation_;
	int generations_;
	bool isActive_;

public:
	Asteroid();
	Asteroid(Vector2D pos, Vector2D vel, double w, double h, double r, int g, bool active = false);
	~Asteroid();

	// Position
	inline const Vector2D& getPos() const { return position_; }
	inline void setPos(const Vector2D& pos) { position_.set(pos); }
	inline void setPos(double x, double y) { position_.set(x, y); }
	inline void setPosX(double x) { position_.setX(x); }
	inline void setPosY(double y) { position_.setY(y); }

	// Rotation
	inline double getRot() const { return rotation_; }
	inline void setRot(double angle) { rotation_ = angle; }

	// Velocity
	inline const Vector2D& getVel() const { return velocity_; }
	inline void setVel(const Vector2D& vel) { velocity_.set(vel); }
	inline void setVel(double x, double y) { velocity_.set(x, y); }
	inline void setVelX(double x) { velocity_.setX(x); }
	inline void setVelY(double y) { velocity_.setY(y); }

	// Scale
	inline double getW() const { return width_; }
	inline double getH() const { return height_; }
	inline void setW(double width) { width_ = width; }
	inline void setH(double height) { height_ = height; }
	inline void setWH(double width, double height) { width_ = width; height_ = height; }

	// Generations
	inline int getGenerations() const { return generations_; }
	inline void setGenerations(int g) { generations_ = g; }

	// Active
	inline bool getActive() const { return isActive_; }
	inline void setActive(bool active) { isActive_ = active; }
};

#endif // !__ASTEROID_H__