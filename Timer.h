#ifndef _TIMER_H
#define _TIMER_H


//Include files
#include "BaseObject.h"


class Timer :public BaseObject
{
public:
	//constructor
	Timer(const std::tstring& name);
	//Destructor
	virtual ~Timer();

	//Copy constructor & Assignment operator
	Timer(const Timer& tRef);
	Timer& operator=(const Timer& tRef);

	//void* operator new(size_t size);
	//void operator delete(void* pdelete);

	//Methods
	bool Initialize();
	bool PostInitialize();
	bool Update(Context& context);
	bool ShutDown();

	float GetTotalTime();
	float GetDeltaTime();

	void Reset();

private:
	//Methods
	void Start();
	void Stop();

	//Members
	double m_SecondsPerCount;
	double m_DeltaTime;

	__int64 m_BaseTime;
	__int64 m_PauseTime;
	__int64 m_StopTime;
	__int64 m_PrevTime;
	__int64 m_CurrTime;

	bool m_bStopped;

};


#endif // !_TIMER_H
