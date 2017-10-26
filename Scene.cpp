#include "Scene.h"



Scene::Scene(const std::tstring& name)
	:BaseObject(name)
{
	TYPE_REGISTER(Scene);
}


Scene::~Scene()
{
}
bool Scene::Initialize()
{
	return BaseObject::Initialize();
}
bool Scene::PostInitialize() 
{
	return BaseObject::PostInitialize();
}
bool Scene::LoadContent() 
{
	return BaseObject::LoadContent();
}
bool Scene::PostLoadContent() 
{
	return BaseObject::PostLoadContent();
}
bool Scene::Update(Context& context) 
{
	return BaseObject::Update(context);
}
bool Scene::Draw(Context& context) 
{
	return BaseObject::Draw(context);
}
bool Scene::DrawUI(Context& context) 
{
	return BaseObject::DrawUI(context);
}
bool Scene::ShutDown() 
{
	return BaseObject::ShutDown();
}