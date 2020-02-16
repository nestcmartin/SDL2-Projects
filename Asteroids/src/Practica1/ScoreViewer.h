#ifndef __SCORE_VIEWER_H__
#define __SCORE_VIEWER_H__

#include "Component.h"
#include "ScoreManager.h"

class ScoreViewer : public Component 
{
private:
	ScoreManager* scoreManager_;

public:
	ScoreViewer();
	virtual ~ScoreViewer();
	
	void init() override;
	void draw() override;
};

#endif // !__SCORE_VIEWER_H__