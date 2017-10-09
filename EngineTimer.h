#ifndef _ENGINETIMER_H
#define _ENGINETIMER_H

//Include files
#include "System.h"

//Additional include files
#ifndef _VECTOR_
#include<vector>
#endif // !_VECTOR_
#ifndef _STRING_H
#include"string.h"
#endif // !_STRING_H

//Forward Decleration
class Timer;

//struct
struct EngineTimerData : public SystemData {
	EngineTimerData() :SystemData(SystemType::Sys_EngineTimer) {

	}
};



//Class EngineTimer 
class EngineTimer :	public System
{ 

	friend class Engine;

public:

	//destructor
	virtual ~EngineTimer();

	Timer* GetWorldTimer() { return m_pWorldTimer; }

	void AddTimer(const std::tstring& name);
	Timer* GetTimer(const std::tstring& name);

	//void* operator new(size_t size);
	//void operator delete(void*pdelete);

	//Methods
	bool Initialize();
	bool Update(Context& context);
	bool ShutDown();

protected:

	//constructor 
	EngineTimer(const EngineTimerData& data);

private:
	//Methods
	//Members
	Timer* m_pWorldTimer;
	std::vector<Timer*> m_vecTimers;
};

#endif