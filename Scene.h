#ifndef _SCENE_H
#define _SCENE_H

#include "BaseObject.h"

#ifndef _CONTEXT_H
#include"context.h"
#endif // !_CONTEXT_H

#ifndef _STRING_H
#include "string.h"
#endif // !_STRING_H

#ifndef _SCENEFACTORY_H
#include"SceneFactory.h"
#endif // !_SCENEFACTORY_H


class Scene :public BaseObject
{
	TYPE_INIT(Scene);
public:
	Scene(const std::tstring& name);
	virtual ~Scene();

	//TODO: Add methods to add gameobjects to the scene
	//TODO: Add methods to remova gameobjects from the scene

	virtual bool Initialize();
	virtual bool PostInitialize();
	virtual bool LoadContent();
	virtual bool PostLoadContent();
	virtual bool Update(Context& context);
	virtual bool Draw(Context& context);
	virtual bool DrawUI(Context& context);

	virtual bool ShutDown();

	//TODO: get the contentManager from the scene
	//ToDo: Find Gameobjects inside the scene
protected:

private:

};
#endif // !_SCENE_H 