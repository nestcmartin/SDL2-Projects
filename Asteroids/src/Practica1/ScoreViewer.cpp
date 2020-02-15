#include "ScoreViewer.h"

#include "Texture.h"
#include "Entity.h"
#include "SDL_macros.h"

ScoreViewer::ScoreViewer() :
	Component(ECS::ScoreViewer),
	scoreManager_(nullptr) {
}

ScoreViewer::~ScoreViewer() {
}

void ScoreViewer::init() {
	scoreManager_ = GETCMP1_(ScoreManager);
}

void ScoreViewer::draw() {

	Texture score(game_->getRenderer(), "Nuria Guapa", *(game_->getFontManager()->getFont(Resources::ARIAL24)), { COLOR(0x111122ff) });
	score.render(game_->getRenderer(), game_->getWindowWidth() / 2 - score.getWidth() / 2, 10);
}
