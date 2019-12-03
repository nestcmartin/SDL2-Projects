#ifndef __FILE_NOT_FOUND_ERROR_H__
#define __FILE_NOT_FOUND_ERROR_H__

#include "ArrowsError.h"

class FileNotFoundError : public ArrowsError
{
public:
	FileNotFoundError(const std::string& msg) : ArrowsError(msg) {};
};

#endif // !__FILE_NOT_FOUND_ERROR_H__