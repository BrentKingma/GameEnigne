#pragma once
#include <exception>
#include <string>

class BlueException : public std::exception
{
public:
	BlueException(int lineNum, const char* file) noexcept;
	const char* what() const noexcept override;
	virtual const char* GetType() const noexcept;
	int GetLine() const noexcept;
	const std::string& GetFile() const noexcept;
	std::string GetOriginString() const noexcept;
private:
	int lineNum;
	std::string file;
protected:
	///Mutable allows for editing inside const function
	mutable std::string whatBuffer;
};