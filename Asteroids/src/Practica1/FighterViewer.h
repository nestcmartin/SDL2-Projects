#ifndef __FIGHTER_VIEWER_H__
#define __FIGHTER_VIEWER_H__

#include <algorithm>

#include "Component.h"
#include "Texture.h"
#include "Transform.h"

class FighterViewer : public Component
{
private:
	Texture* texture_;
	Transform* transform_;

public:
	FighterViewer();
	FighterViewer(Texture* texture);
	virtual ~FighterViewer();

	void init() override;
	void draw() override;
};

#endif // !__FIGHTER_VIEWER_H__
