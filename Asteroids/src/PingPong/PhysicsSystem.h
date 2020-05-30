#pragma once
#include "System.h"
#include "Transform.h"

class PhysicsSystem: public System {
public:
	PhysicsSystem();
	virtual ~PhysicsSystem();
    void recieve(const msg::Message& msg) override;
	void init() override;
	void update() override;
	void resetBallPosition();
	Vector2D resetBallVelocity();

private:
	void moveBall(Transform *ballTR);
	void movePaddleWithMouse(Transform *p, double mouseYPos);
	bool checkSidesCollision(Transform *ballTR, Transform *leftPaddleTR, Transform *rightPaddleTR);
	bool checkBottomUpCollision(Transform *ballTR, Transform *leftPaddleTR, Transform *rightPaddleTR);
	bool checkBallPaddlesCollision(Transform *ballTR, Transform *leftPaddleTR, Transform *rightPaddleTR);

};

