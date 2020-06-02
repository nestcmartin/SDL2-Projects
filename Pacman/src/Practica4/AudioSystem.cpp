#include "AudioSystem.h"

#include "SDLGame.h"

AudioSystem::AudioSystem() :
	System(ECS::_sys_Sound)
{
}

void AudioSystem::init()
{
	game_->getAudioManager()->playMusic(Resources::PacMan_Intro);
}

void AudioSystem::update()
{
}

void AudioSystem::receive(const msg::Message& msg)
{
	switch (msg.id)
	{
	case msg::_GAME_START:
		game_->getAudioManager()->haltMusic();
		break;

	case msg::_FOOD_COLLISION:
		game_->getAudioManager()->playChannel(Resources::PacMan_Eat, 0);
		break;

	case msg::_PACMAN_LOSE:
		game_->getAudioManager()->haltMusic();
		game_->getAudioManager()->playChannel(Resources::PacMan_Death, 0);
		break;

	case msg::_PACMAN_WIN:
		game_->getAudioManager()->haltMusic();
		game_->getAudioManager()->playChannel(Resources::PacMan_Won, 0);
		break;

	case msg::_RESET:
		game_->getAudioManager()->haltMusic();
		game_->getAudioManager()->playMusic(Resources::PacMan_Intro);
		break;
	}
}
