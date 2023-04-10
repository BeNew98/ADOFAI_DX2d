#include "PrecompileHeader.h"
#include "GameEngineTime.h"

GameEngineTime GameEngineTime::GlobalTime;

GameEngineTime::GameEngineTime() 
{
	QueryPerformanceFrequency(&Second);
	QueryPerformanceCounter(&Prev);
}

GameEngineTime::~GameEngineTime() 
{
}

void GameEngineTime::Reset()
{
	QueryPerformanceCounter(&Prev);
}

float GameEngineTime::TimeCheck()
{
	QueryPerformanceCounter(&Current);

	Tick = Current.QuadPart - Prev.QuadPart;

	DoubleDeltaTime = (static_cast<double>(Current.QuadPart) - static_cast<double>(Prev.QuadPart)) / static_cast<double>(Second.QuadPart);

	Prev.QuadPart = Current.QuadPart;

	FloatDeltaTime = static_cast<float>(DoubleDeltaTime);

	return FloatDeltaTime;
}

