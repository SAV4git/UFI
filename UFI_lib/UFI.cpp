/*
 *User Friendly Interface
*/
#include "../UFI_lib/UFI.h"
#include "../UFI_lib/UFI_Types.h"
#include <iomanip>
#include <stdio.h>
#include <list>
#include <vector>

using std::cout;
using std::endl;
using std::setw;
using std::left;
using std::right;

using EvFlag = Uint64;

UFI_EventHendler	Event;
UFI_EventHendler	Menu1;
UFI_EventHendler	Menu2;

UFI_Mouse		Mouse;//kill
UFI_Keyboard	KeyB;//kill
UFI_Event 	Ev;

UFIs_Event Evnt;
UFIs_EvFlagMask EvFlagsMask;

UFI_Color_s Color;

RenderList_t		RendList;
RenderLineList_t	RendLineList;
RenderGraphList_t	RendGraphList;

bool UpdateObj = false;
Uint64 TimeForUpdateObj[2];

//################################################################################

extern int64_t timespecDiff(struct timespec *timeA_p, struct timespec *timeB_p)
{
  return ((timeA_p->tv_sec * 1000000000) + timeA_p->tv_nsec) -
           ((timeB_p->tv_sec * 1000000000) + timeB_p->tv_nsec);
}

/*
 * Calculate Rectengle Points
 */
extern void CalculatePoints(UFI_RenderObject_t* RendObj_ptr){
	
	UFI_RectPoints_t *temp_point;
	UFI_Rect_t *temp_Rect;
	
	temp_point = &RendObj_ptr->Rect.Point;
	temp_Rect =	&RendObj_ptr->Rect;
	
	temp_point->Top_L.x = temp_Rect->Output.x;
	temp_point->Top_L.y = temp_Rect->Output.y;
	temp_point->Top_R.x = temp_point->Top_L.x + temp_Rect->Output.w;
	temp_point->Top_R.y = temp_point->Top_L.y;
	temp_point->Bot_L.x = temp_point->Top_L.x;
	temp_point->Bot_L.y = temp_point->Top_L.y + temp_Rect->Output.h;
	temp_point->Bot_R.x = temp_point->Top_R.x;
	temp_point->Bot_R.y = temp_point->Bot_L.y;
	temp_point->Center.x = temp_Rect->Output.x + temp_Rect->Output.w/2;
	temp_point->Center.x = temp_Rect->Output.y + temp_Rect->Output.h/2;
}

extern UFI_RectPoints_t CalculatePoints(SDL_Rect* Rect){
	
	UFI_RectPoints_t temp_point;
	SDL_Rect *temp_Rect;
	
	temp_Rect = Rect;
	
	temp_point.Top_L.x = temp_Rect->x;
	temp_point.Top_L.y = temp_Rect->y;
	temp_point.Top_R.x = temp_point.Top_L.x + temp_Rect->w;
	temp_point.Top_R.y = temp_point.Top_L.y;
	temp_point.Bot_L.x = temp_point.Top_L.x;
	temp_point.Bot_L.y = temp_point.Top_L.y + temp_Rect->h;
	temp_point.Bot_R.x = temp_point.Top_R.x;
	temp_point.Bot_R.y = temp_point.Bot_L.y;
	temp_point.Center.x = temp_Rect->x + temp_Rect->w/2;
	temp_point.Center.x = temp_Rect->y + temp_Rect->h/2;
	
	return temp_point;
}

extern void PrintRendObjParam(UFI_RenderObject_t* RendObj_ptr){
	cout << "-------------------------------------------------------" << endl;
	cout << "Texture "<< RendObj_ptr->Texture << ", Name = "<< RendObj_ptr->Name << endl;
	cout << "Source" << endl; 
	cout	<< "      h=" << setw(4) << right<< RendObj_ptr->Rect.Source.h 
			<< ", w=" << setw(4) << right << RendObj_ptr->Rect.Source.w << endl;
	
	cout	<< "      x=" << setw(4) << right << RendObj_ptr->Rect.Source.x
			<< ", y=" << setw(4) << right << RendObj_ptr->Rect.Source.y << endl;
	cout << "Output" << endl;
	cout	<< "      h=" << setw(4) << right<< RendObj_ptr->Rect.Output.h 
			<< ", w=" << setw(4) << right << RendObj_ptr->Rect.Output.w << endl;
	
	cout	<< "      x=" << setw(4) << right << RendObj_ptr->Rect.Output.x
			<< ", y=" << setw(4) << right << RendObj_ptr->Rect.Output.y << endl;
}

extern void PrintAllRendObjParam(){
	cout << "===========================================================" << endl;
	for( auto iter = RendList.begin(); iter != RendList.end(); iter++){
		PrintRendObjParam(*iter);
	}
	cout << "===========================================================" << endl;
}

extern void Counter(){
	static int s = 0; s++;
	cout << "s = " << s << endl; 
}



UFI::UFI()
{
}

UFI::~UFI()
{
}



