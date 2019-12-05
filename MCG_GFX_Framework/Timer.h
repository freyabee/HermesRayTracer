#pragma once
#include <Windows.h>
#include <ctime>
#include <iostream>
class Timer
{
public:
	Timer();
	~Timer();

	void Start();
	void Stop();
	void Reset();
	void PrintTime();
	float GetValue();

private:
	double freq;
	std::clock_t start;


};

