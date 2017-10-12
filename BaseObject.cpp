#include "BaseObject.h"
 

BaseObject::BaseObject() 
	:m_Name(_T("")),
m_ID(ObjectCounter<BaseObject>::GetAmount()),
m_bIsInitialized(false),
m_bIsPostInitialized(false),
m_bIsContentLoaded(false),
m_bIsPostContentLoaded(false),
m_bIsDestroyed(false),
m_bCanDraw(true),
m_bCanTick(true)
{
	TYPE_REGISTER(BaseObject);

	m_Name = _T("Object_")+TOSTRING(m_ID); 
} 

BaseObject::BaseObject(const std::tstring& name)
	:m_Name(name),
	m_ID(ObjectCounter<BaseObject>::GetAmount()),
	m_bIsInitialized(false),
	m_bIsPostInitialized(false),
	m_bIsContentLoaded(false),
	m_bIsPostContentLoaded(false),
	m_bIsDestroyed(false),
	m_bCanDraw(true),
	m_bCanTick(true)
{ 
	TYPE_REGISTER(BaseObject);
}
BaseObject::BaseObject(ObjectData* data)
	:m_Name(data->name),
	m_ID(ObjectCounter<BaseObject>::GetAmount()),
	m_bIsInitialized(false),
	m_bIsPostInitialized(false),
	m_bIsContentLoaded(false),
	m_bIsPostContentLoaded(false),
	m_bIsDestroyed(false),
	m_bCanDraw(true),
	m_bCanTick(true)
{
	TYPE_REGISTER(BaseObject);
}

BaseObject::~BaseObject()
{ 
	SafeDelete(m_pData);
}

void BaseObject::Reset() {

}
bool BaseObject::IsType(const std::tstring& type) {
	return Singleton<TypeChecker>::GetInstance()->IsType(GetID(), type);
}
bool BaseObject::IsA(const std::tstring& type) {
	return Singleton<TypeChecker>::GetInstance()->IsA(GetID(), type);
}