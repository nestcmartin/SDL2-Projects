#ifndef __ARROWS_ERROR_H__
#define __ARROWS_ERROR_H__

#include <stdexcept>

class ArrowsError : public std::logic_error
{
public:
	ArrowsError(const std::string& msg) : std::logic_error(msg) {}
	virtual const char* what() { return std::logic_error::what(); }
};

#endif // !__ARROWS_ERROR_H__