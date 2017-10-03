#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "UObject.h"

//Additional Include Files
#ifndef _CONTEXT_H
#include "context.h"
#endif


//Enumaration
enum SystemType
{
	Sys_Invalid,
	Sys_Window,
	Sys_Game,
	Sys_Input,
	Sys_Graphics,
	Sys_GameTimer,

	Sys_MAX
};

//Structs
struct SystemData
{
	SystemData();
	SystemData(const SystemType& type);

	SystemType systemType;

};

class System :public UObject
{
	friend class Engine;
	
public:
	System(const SystemData& data);
	virtual ~System();

	virtual bool Initialize() { return UObject::Initialize(); }
	virtual bool Update(Context& context) { return UObject::Update(context); }
	virtual bool ShutDown() { return UObject::ShutDown(); }

	SystemType GetType() { return m_SystemType; }

protected:
	SystemType m_SystemType;
};


#endif // !_SYSTEM_H