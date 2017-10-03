#ifndef _DELETEMACRO_H
#define _DELETEMACRO_H

//defines
#define SafeRelease(x) { if(x){x->Release(); x=nullptr;}}// Macro for releasing COM objects
#define SafeDelete(x) { if(x){delete x; x=nullptr;}}// Macro for deleting objects




#endif // !_DELETEMACRO_H
