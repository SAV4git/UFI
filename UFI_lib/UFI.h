#ifndef UFI_H
#define UFI_H

//sudo apt-get install libsdl2-dev
//sudo apt-get install libsdl2-2.0
//sudo apt-get install libsdl2-ttf
//sudo apt-get install libsdl2-ttf-dev

//g++ -O3 UFI_Texture.cpp UFI_Render.cpp UFI_Module.cpp UFI_EventController.cpp UFI.cpp main.cpp -std=c++1y -lSDL2 -lSDL2_ttf -o UFI_test  && ./UFI_test

#include "../UFI_lib/UFI_Types.h"

#include "../UFI_lib/UFI_Line.h"
#include "../UFI_lib/UFI_Texture.h"
#include "../UFI_lib/UFI_EventController.h"
#include "../UFI_lib/UFI_Module.h"
#include "../UFI_lib/UFI_Window.h"
#include "../UFI_lib/UFI_Anim.h"

#include "../UFI_lib/UFI_Debug.h"


extern bool loop;

extern UFI_EventHendler	Event;
extern UFI_EventHendler	Menu1;
extern UFI_EventHendler	Menu2;

extern UFI_Event		Ev;
extern SDL_Event		event;
extern UFIs_EvFlagMask	EvFlagsMask;

extern UFI_Color_s 		Color;

extern bool 	UpdateObj;
extern Uint64	TimeForUpdateObj[2];

#define DEBUG_SLOWMO false

void Window_init(void);
void SDL_Destructor(void);
void Setup(void);
void Loop(void);
void Processing_Display(void);
void Createing_textures(void);
bool SetupTTF( const char *);
void CreateTextTextures(void);
void Creating_Modules(void);
void Counter();

//################################################################################

extern uint64_t timeElapsed;
extern Uint32 timeFiltered;
extern struct timespec start_time, end_time;

extern void CalculatePoints( UFI_RenderObject_t* );
extern UFI_RectPoints_t CalculatePoints( SDL_Rect* );
extern void PrintRendObjParam(UFI_RenderObject_t*);
extern void PrintAllRendObjParam();

extern int64_t timespecDiff(struct timespec*, struct timespec*);



class UFI
{
public:
	UFI();
	~UFI();
};

#endif // UFI_H
