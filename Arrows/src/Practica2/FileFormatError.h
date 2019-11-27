#ifndef __FILE_FORMAT_ERROR_H__
#define __FILE_FORMAT_ERROR_H__

#include "ArrowsError.h"

class FileFormatError : public ArrowsError
{
public:
	FileFormatError(const std::string& msg) : ArrowsError(msg) {};
};

#endif // !__FILE_FORMAT_ERROR_H__