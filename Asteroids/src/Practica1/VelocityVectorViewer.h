#ifndef __VELOCITY_VECTOR_VIEWER_H__
#define __VELOCITY_VECTOR_VIEWER_H__

#include "Component.h"
#include "Transform.h"

class VelocityVectorViewer : public Component 
{
private:
	Transform* transform_;

public:
	VelocityVectorViewer();
	virtual ~VelocityVectorViewer();

	void init() override;
	void draw() override;
};

#endif // !__VELOCITY_VECTOR_VIEWER_H__