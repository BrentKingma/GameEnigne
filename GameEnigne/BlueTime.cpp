#include "BlueTime.h"

using namespace std::chrono;

BlueTime::BlueTime()
{
	last = steady_clock::now();
}

float BlueTime::Mark()
{
	const auto old = last;
	last = steady_clock::now();
	const duration<float> frameTime = last - old;
	return frameTime.count();
}

float BlueTime::Peek() const
{
	return duration<float>(steady_clock::now() - last).count();
}