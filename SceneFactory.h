#ifndef _SCENEFACTORY_H
#define _SCENEFACTORY_H

#ifndef _MAP_H
#include<map>
#endif // !_MAP_H

#ifndef _STRING_H
#include"string.h"
#endif // !_STRING_H

#include"Singleton.h"

//Forward Decleration
class Scene;

//Defines
#define REGISTER_DEC_TYPE(NAME) static TypeRegister<NAME> reg
#define REGISTER_DEF_TYPE(NAME) TypeRegister<NAME> NAME::reg(_T(#NAME))

class SceneFactory
{
public:
	SceneFactory();
	~SceneFactory();

	static Scene* CreateObject(const std::tstring& s);
	static void ClearScenes();

protected:
	static std::map<std::tstring, Scene*>* GetMap();
private:
	static std::map<std::tstring, Scene*>* map;
};

template<typename T>
class TypeRegister:public SceneFactory
{
public:
	TypeRegister(const std::tstring& name) {
		GetMap()->insert(std::make_pair(s,new T(s)))
	}

};
 

#endif // !_SCENEFACTORY_H