#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "Vector2D.h"
#include "Component.h"

class Transform : public Component 
{
private:
	Vector2D position_;
	Vector2D velocity_;
	double width_;
	double height_;
	double rotation_;

public:
	Transform();
	Transform(Vector2D pos, Vector2D vel, double width, double height, double rotation);
	virtual ~Transform();

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
};

#endif // !__TRANSFORM_H__