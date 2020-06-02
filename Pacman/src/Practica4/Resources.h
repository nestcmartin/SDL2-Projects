#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include <string>
#include <vector>
#include <SDL.h>

class Resources
{
public:

	enum TextureId : std::size_t
	{
		// Images
		PacManSprites,

		// Text
		PressEnterToStartANewGame,
		PressEnterToContinue,
		GameOver
	};

	enum AudioId : std::size_t
	{
		// Music
		PacMan_Intro,

		// SoundS
		PacMan_Eat,
		PacMan_Death,
		PacMan_Won
	};

	enum FontId : std::size_t
	{
		ARIAL16,
		ARIAL24
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