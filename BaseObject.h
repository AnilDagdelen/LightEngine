#ifndef _BaseObject_H
#define _BaseObject_H

//Additional include files

#ifndef _CONTEXT_H
#include "context.h"
#endif // !_CONTEXT_H

#ifndef  _STRING_H
#include "string.h"
#endif // ! _STRING_H

#ifndef _OBJECTCOUNTER_H
#include"ObjectCounter.h"
#endif // !_OBJECTCOUNTER_H

#ifndef _SINGLETON_H
#include"Singleton.h"
#endif // !_SINGLETON_H

#ifndef _TYPECHECKER_H
#include "TypeChecker.h"
#endif // !_TYPECHECKER

//struct
struct ObjectData
{
	ObjectData() :name(_T(""))
	{

	}
	ObjectData(const std::tstring& n):name(n)
	{

	}

	//void* operator new(size_t size);
	//void operator delete(void* pdelete);

	std::tstring name;

};


//Define
//Register the type inside the typechecker class
#define TYPE_REGISTER(class_type_id)\
Singleton<TypeChecker>::GetInstance(true)->AddType(GetID(),_T(#class_type_id))
//Initialize the class type with hardcoded methods
#define TYPE_INIT(class_type_id)\
static const std::tstring GetClassTypeId(){return _T(#class_type_id);}\
virtual const std::tstring GetTypeId() const {return _T(#class_type_id);}

class BaseObject:public ObjectCounter<BaseObject>
{
	TYPE_INIT(BaseObject);

public:
	BaseObject();
	BaseObject(const std::tstring& name);
	BaseObject(ObjectData* data);
	virtual ~BaseObject();

/*
	void* operator new(size_t size);
	void operator delete(void* pdelete);*/

	virtual bool Initialize()					 { m_bIsInitialized = true; return true; }
	virtual bool PostInitialize()				 { m_bIsPostInitialized = true; return true; }
	virtual bool LoadContent()					 { m_bIsContentLoaded = true; return true; }
	virtual bool PostLoadContent()				 { m_bIsPostContentLoaded = true; return true; }
	virtual bool Update(Context& context)		 { return true; }
	//virtual bool LateUpdate(Context& context)  {return true;}
	virtual bool Draw(Context& context)			 { return true; }
	virtual bool DrawUI(Context& context)		 { return true; }
	virtual bool ShutDown()						 { return true; }

	virtual void Reset();

	void SetName(const std::tstring& name) { m_Name = name; }
	const std::tstring& GetName() { return m_Name; }

	bool IsInitialized() const { return m_bIsInitialized; }
	bool IsPostInitialized() const { return m_bIsPostInitialized; }
	bool IsContentLoaded() const { return m_bIsContentLoaded; }
	bool IsPostContentLoaded() const { return m_bIsPostContentLoaded; }
	
	void SetCanTick(bool canTick) { m_bCanTick = canTick; }
	bool CanTick()  const { return m_bCanTick; }
	void SetCanDraw(bool canDraw) { m_bCanDraw = canDraw; }
	bool CanDraW()  const { return m_bCanDraw; }

	void Destroy() { m_bIsDestroyed=true; }
	bool IsDestroyed() const { return m_bIsDestroyed; }

	void Activate() { m_bIsActivated = true; }
	void DeActivate() { m_bIsActivated = false; }
	bool IsActivate() { return m_bIsActivated; }

	template<typename T>
	T* GetObjectData() {
		return static_cast<T*>(m_pData);
	}
	ObjectData* GetRawObjectData() {
		return m_pData;
	}


	int GetID(){ return m_ID; }
	int GetObjectAmount() { return ObjectCounter<BaseObject>::GetAmount(); }

	bool IsType(const std::tstring& type);
	bool IsA(const std::tstring& type);

protected:

	int m_ID;

	bool m_bIsInitialized;
	bool m_bIsPostInitialized;

	bool m_bIsContentLoaded;
	bool m_bIsPostContentLoaded;

	std::tstring m_Name;

	ObjectData* m_pData;


private:

	bool m_bIsActivated;
	bool m_bIsDestroyed;

	bool m_bCanTick;
	bool m_bCanDraw;




};
 

#endif // !_BaseObject_H
