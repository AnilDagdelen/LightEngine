#include "Timer.h"

#ifndef _WINDIWS
#include <Windows.h>
#endif // !_WINDIWS


//#include "MemoryManager.h.h"
//#include "Logger.h.h"

#ifndef _CTIME_
#include<ctime>
#endif // !_CTIME_



Timer::Timer(const std::tstring& name):BaseObject(name),
m_SecondsPerCount(0.0),
m_DeltaTime(-1.0),
m_BaseTime(0),
m_PauseTime(0),
m_PrevTime(0),
m_CurrTime(0),
m_bStopped(false)
{
	__int64 countpersec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countpersec);
	m_SecondsPerCount = 1.0 / (double)countpersec;
	
}


Timer::~Timer()
{
}

//#pragma region New & Delete Operator
//void* EngineTimer::operator new(size_t size) {
//	return MEMORYMANAGER->Alloc(size);
//}
//void EngineTimer::operator delete(void* pdelete) {
//	MEMORYMANAGER->Free(pdelete);
//}
//#pragma endregion

bool Timer::Initialize() {

	BaseObject::Initialize();
	Start();

	return true;
}
bool Timer::PostInitialize() { 
	return BaseObject::PostInitialize();
}
bool Timer::Update(Context& context) {
	BaseObject::Update(context);
	if (m_bStopped)
	{
		m_DeltaTime = 0.0;
		return true;
	}
	//Get the time this frame
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_CurrTime = currTime;

	//Time difference between this frame and the previous one
	m_DeltaTime = (m_CurrTime - m_PrevTime)*m_SecondsPerCount;

	//Prepare the next frame
	m_PrevTime = m_CurrTime;

	//Force nonnegative
	//The DXSKS's CDXUTTimer metions that if the processor goes into power save mode or we get shuffled to another processor
	//then DeltaTime can be negative

	if (m_DeltaTime < 0.0)
		m_DeltaTime = 0.0;

	return true;

}
bool Timer::ShutDown() { 
	BaseObject::ShutDown();

	Stop();

	return true;
}


float Timer::GetTotalTime() {
	if (m_bStopped)
		return (float)((m_StopTime - m_BaseTime)*m_SecondsPerCount);
	else
		return (float)(((m_CurrTime - m_PauseTime) - m_BaseTime)*m_SecondsPerCount);
}
float Timer::GetDeltaTime() {
	return (float)m_DeltaTime;
}
void Timer::Reset() {
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	m_BaseTime = currTime;
	m_PrevTime = currTime;
	m_StopTime = 0;

	m_bStopped = false;
}
void Timer::Start() {
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime);
	m_PrevTime = startTime;

	//If we are resuming the timer from a stopped state..

	if (m_bStopped)
	{
		//then accumulate the paused time
		m_PauseTime += (startTime - m_StopTime);
		//Since ew are starting the timer back up,
		//the current previous is not valid
		//as it occured while paused,
		//so reset it to the current tiöe
		m_PrevTime = startTime;

		//no longer stopped
		m_StopTime = 0;
		m_bStopped = false;
	}
}
void Timer::Stop() {
	//if we are already stopped then dont do anything
	if (m_bStopped)
		return;
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	//Save the time we stopped at
	//and set the boolean flan indication the timer stopped
	m_StopTime = currTime;
	m_bStopped = false;

}
