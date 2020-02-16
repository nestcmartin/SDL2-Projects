#ifndef __ASTEROIDS_VIEWER_H__
#define __ASTEROIDS_VIEWER_H__

#include "Texture.h"
#include "Component.h"
#include "AsteroidsPool.h"

class AsteroidsViewer : public Component
{
private:
	Texture* texture_;
	AsteroidsPool* asteroidsPool_;

public:
	AsteroidsViewer();
	AsteroidsViewer(Texture* texture);
	virtual ~AsteroidsViewer();

	void init() override;
	void draw() override;
};

#endif // !__ASTEROIDS_VIEWER_H__