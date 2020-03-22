#include "Resources.h"

#include "SDL_Macros.h"

std::vector<Resources::ImageInfo> Resources::images_
{
	{ Airplanes, "resources/images/airplanes.png" },
	{ Asteroid, "resources/images/asteroid.png" },
	{ Badges, "resources/images/badges.png" },
	{ BlackHole, "resources/images/black-hole.png" },
	{ Explosion, "resources/images/explosion.png" },
	{ Heart, "resources/images/heart.png" },
	{ SpaceShips, "resources/images/spaceships.png" },
	{ Star, "resources/images/star.png" },
	{ Bullet, "resources/images/whiterect.png" },
	{ PacMan, "resources/images/pacman.png" }
};

std::vector<Resources::TextMsgInfo> Resources::messages_
{
	{ HelloWorld, "Hello World", { COLOR(0xaaffffff) }, ARIAL16 },
	{ PresAnyKey, "Press Any Key To Start...", { COLOR(0xaaffbbff) }, ARIAL24 },
	{ GameOverWin, "Game Over! You Win!", { COLOR(0xffffbbff) }, ARIAL24 },
	{ GameOverLose, "Game Over! You Lose!", { COLOR(0xffffbbff) }, ARIAL24 }
};

std::vector<Resources::MusicInfo> Resources::musics_
{
	{ Boooo, "resources/sound/boooo.wav" },
	{ Cheer, "resources/sound/cheer.wav" },
	{ ImperialMarch, "resources/sound/imperial_march.wav" }
};

std::vector<Resources::SoundInfo> Resources::sounds_
{
	{ ExplosionSound, "resources/sound/explosion.wav" },
	{ GunShot, "resources/sound/gunshot.wav" }
};

std::vector<Resources::FontInfo> Resources::fonts_
{
	{ ARIAL16, "resources/fonts/ARIAL.ttf", 16 },
	{ ARIAL24, "resources/fonts/ARIAL.ttf", 24 },
	{ CAPTURE16, "resources/fonts/Capture_it.ttf", 16 },
	{ CAPTURE24, "resources/fonts/Capture_it.ttf", 24 },
	{ NES16, "resources/fonts/NES-Chimera.ttf", 16 },
	{ NES24, "resources/fonts/NES-Chimera.ttf", 24 },
	{ PAINT16, "resources/fonts/Paintbrush.ttf", 16 },
	{ PAINT24, "resources/fonts/Paintbrush.ttf", 24 },
	{ PIXEL16, "resources/fonts/Pixeled.ttf", 16 },
	{ PIXEL24, "resources/fonts/Pixeled.ttf", 24 },
};