#ifndef __BULLETS_VIEWER_H__
#define __BULLETS_VIEWER_H__

#include "Texture.h"
#include "Component.h"
#include "BulletsPool.h"

class BulletsViewer : public Component
{
private:
	Texture* texture_;
	BulletsPool* bulletsPool_;

public:
	BulletsViewer();
	BulletsViewer(Texture* texture);
	virtual ~BulletsViewer();

	void init() override;
	void draw() override;
};
#endif // !__BULLETS_VIEWER_H__
