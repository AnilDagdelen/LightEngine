#ifndef _TYPECHECKER_H
#define _TYPECHECKER_H

#ifndef _VECTOR_H
#include<vector>
#endif // !_VECTOR_H
#ifndef _MAP_
#include <map>
#endif // !_MAP_
#ifndef _STRING_H
#include "string.h"
#endif // !_STRING_H

#ifndef _SINGLETON_H
#include "Singleton.h"
#endif // !_SINGLETON_H



class TypeChecker
{
public:
	TypeChecker();
	~TypeChecker();

	//void* operator new (size_t size);
	//void operator delete(void* pdelete);

	void AddType(int objectID,const std::tstring& type);
	const std::tstring& GetType(int objectID);

	bool IsType(int objectID,const std::tstring& type);
	bool IsType(const std::tstring& type,const std::tstring& isType);
	bool IsA(int objectID, const std::tstring& type);
	bool IsA(const std::tstring& type, const std::tstring& isType);

protected:
	bool TypeExists(const std::tstring& type,bool last=true);
	bool TypeExists(const std::tstring& type,std::map<int,std::vector<std::tstring>>::iterator ref_it,bool last=true);

	std::map<int, std::vector<std::tstring>> m_mapTypes;
	std::tstring m_invalidType;

};


#endif // !_TYPECHECKER_H