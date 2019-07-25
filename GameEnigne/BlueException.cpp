#include "BlueException.h"
#include <sstream>;

BlueException::BlueException(int lineNum, const char* file) noexcept : lineNum(lineNum), file(file)
{}

const char* BlueException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl << GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* BlueException::GetType() const noexcept
{
	return "Blue Exception";
}

int BlueException::GetLine() const noexcept
{
	return lineNum;
}

const std::string& BlueException::GetFile() const noexcept
{
	return file;
}

std::string BlueException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "File: " << file << std::endl << "Line: " << lineNum;
	return oss.str();
}