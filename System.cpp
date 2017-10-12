#include "System.h"

SystemData::SystemData()
:ObjectData()
	,systemType(SystemType::Sys_Invalid)
{

}
SystemData::SystemData(const std::tstring& name, const SystemType& type)
	: ObjectData(name)
	,systemType(type)
{

}

System::System(const SystemData& data)
:BaseObject(),
m_SystemType(data.systemType)
{
	SetCanDraw(false);
}

System::~System()
{
}
