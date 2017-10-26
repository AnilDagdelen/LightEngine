#ifndef _SYSTEM_H
#define _SYSTEM_H

#include "BaseObject.h"

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
	Sys_EngineTimer,
	Sys_Logic,

	Sys_MAX
};

//Structs
struct SystemData : ObjectData
{
	SystemData();
	SystemData(const std::tstring& name, const SystemType& type);

	SystemType systemType;

};

class System :public BaseObject
{
	friend class Engine;

public:
	SystemType GetType() { return m_SystemType; }

protected:
	System(const SystemData& data);
	virtual ~System();

	virtual bool Initialize() { return BaseObject::Initialize(); }
	virtual bool Update(Context& context) { return BaseObject::Update(context); }
	virtual bool ShutDown() { return BaseObject::ShutDown(); }


protected:
	SystemType m_SystemType;
};


#endif // !_SYSTEM_H