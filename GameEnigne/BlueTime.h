#pragma once
#include <chrono>

class BlueTime
{
public:
	BlueTime();
	float Mark();
	float Peek() const;
private:
	std::chrono::steady_clock::time_point last;
};