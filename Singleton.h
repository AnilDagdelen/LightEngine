#ifndef _SINGLETON_H
#define _SINGLETON_H

#ifndef _DELETEMACROS_H
#include "deletemacros.h"
#endif // !_DELETEMACROS_H


#include<assert.h>

template<typename T>
class Singleton
{
public:
	~Singleton() {

	}

	static void CreateInstance();
	static void DestroyInstance();

	//void operator delete(void* pdelete) {
	//Singleton<MemoryManager>::GetInstance(true)->free(pdelete);
	//}
	
	static T* GetInstance(bool create = false);

protected:

	Singleton() {
		Singleton::instance = static_cast<T*>(this);
	}

	/*void* operator new (size_t size) {
		return Singleton<MemoryManager>::GetInstance(true)->Alloc(size);
	}*/

	static T* instance;

private:
	Singleton(Singleton const&){}
	Singleton& operator =(Singleton const&){}
};

template <typename T>
T* Singleton<T>::instance = nullptr;

template <typename T>
T* Singleton<T>::GetInstance(bool create) {
	if (create) {
		Singleton<T>::CreateInstance();
	}
	assert(Singleton<T>::instance != nullptr);

	return instance;

}

template <typename T>
void Singleton<T>::CreateInstance() {
	if (Singleton<T>::instance == nullptr)
		Singleton<T>::instance = new T();
}

template <typename T>
void Singleton<T>::DestroyInstance() {
	SafeDelete(Singleton<T>::instance);
}


#endif // !_SINGLETON_H