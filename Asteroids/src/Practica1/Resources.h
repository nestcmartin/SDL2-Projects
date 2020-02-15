#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include <string>
#include <vector>
#include <SDL.h>

class Resources 
{
public:

	enum TextureId : int 
	{
		// Images
		Airplanes,
		Asteroid,
		Badges,
		BlackHole,
		Explosion,
		Heart,
		SpaceShips,
		Star,
		Bullet,

		// Text Messages
		HelloWorld,
		PresAnyKey,
		GameOver
	};

	enum AudioId : int 
	{
		// Music
		Boooo,
		Cheer,
		ImperialMarch,

		// Sound Effects
		ExplosionSound,
		GunShot
	};

	enum FontId : int
	{
		// Fonts
		ARIAL16, 
		ARIAL24,
		CAPTURE16,
		CAPTURE24,
		NES16,
		NES24,
		PAINT16,
		PAINT24,
		PIXEL16,
		PIXEL24
	};

	struct ImageInfo
	{
		TextureId id;
		std::string fileName;
	};

	struct TextMsgInfo
	{
		TextureId id;
		std::string msg;
		SDL_Color color;
		FontId fontId;
	};

	struct MusicInfo 
	{
		AudioId id;
		std::string fileName;
	};

	struct SoundInfo 
	{
		AudioId id;
		std::string fileName;
	};

	struct FontInfo
	{
		FontId id;
		std::string fileName;
		int size;
	};

	static std::vector<ImageInfo> images_; 
	static std::vector<TextMsgInfo> messages_; 
	static std::vector<MusicInfo> musics_; 
	static std::vector<SoundInfo> sounds_; 
	static std::vector<FontInfo> fonts_;

};

#endif // !__RESOURCES_H__