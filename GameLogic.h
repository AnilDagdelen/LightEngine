#ifndef _GAMELOGIC_H
#define _GAMELOGIC_H

//Additional Include Files
#include "System.h"

struct GameLogicData:public SystemData
{
public:
	GameLogicData();
};

class GameLogic :public System
{
	TYPE_INIT(GameLogic);
	friend class Engine;

private:
	GameLogic(const GameLogicData& data);
	virtual ~GameLogic();

	//void* operator new(size_t size);
	//void operator delete(void* pdelete);

	//Overridable Methods
	virtual bool Initialize();
	virtual bool Update(Context& context);
	virtual bool Draw(Context& context);
	virtual bool ShutDown();


};

#endif // !_GAMELOGIC_H