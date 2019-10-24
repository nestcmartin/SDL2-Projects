#ifndef __FILE_NOT_FOUND_ERROR_H__
#define __FILE_NOT_FOUND_ERROR_H__

#include <stdexcept>

class FileNotFoundError : public std::logic_error
{
public:
	FileNotFoundError(const std::string& msg) : logic_error(msg) {};
};

#endif // !__FILE_NOT_FOUND_ERROR_H__