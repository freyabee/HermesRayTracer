#include "Timer.h"



Timer::Timer()
{
}


Timer::~Timer()
{
}

void Timer::Start()
{
	start = std::clock();
	std::cout << "Timer started." << std::endl;
}

void Timer::Stop()
{
	std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
	start = NULL;
}

void Timer::Reset()
{
	start = std::clock();
	std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
}

void Timer::PrintTime()
{
	std::cout << "Time: " << (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms" << std::endl;
}

float Timer::GetValue()
{
	int rtn = (std::clock() - start) / (double)(CLOCKS_PER_SEC / 1000);
	return rtn;
}





