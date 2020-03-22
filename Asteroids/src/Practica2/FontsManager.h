#ifndef __FONTS_MANAGER_H__
#define __FONTS_MANAGER_H__

#include <string>

#include "Font.h"

class FontsManager 
{
public:
	FontsManager();
	virtual ~FontsManager();

	virtual bool init() = 0;

	virtual Font* getFont(int tag) = 0;
	virtual bool loadFont(int tag, std::string fileName, int size) = 0;
};

#endif // !__FONTS_MANAGER_H__