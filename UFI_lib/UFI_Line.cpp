#include "../UFI_lib/UFI.h"
#include "UFI_Line.h"
#include "../UFI_lib/UFI_Types.h"
#include <iostream>

UFI_Line::UFI_Line(int Number_of_lines)
{
	tempLine_ptr = new UFI_Line_t[Number_of_lines];
	LineCount = Number_of_lines;
}

UFI_Line::~UFI_Line()
{
	delete[] tempLine_ptr;
}
void AddPointsToGraph(SDL_Point* Points, int size){
	
}

void UFI_Line::NewLine(int x1, int y1, int x2, int y2, SDL_Color color){
	
	if(LineCount > 0 ){
		LineCount--;
		Count++;
		tempLine_ptr[Count].A.x = x1;
		tempLine_ptr[Count].A.y = y1;
		tempLine_ptr[Count].B.x = x2;
		tempLine_ptr[Count].B.y = y2;
		tempLine_ptr[Count].Color = color;
		tempLine_ptr[Count].Width = 1; //test
		if( tempLine_ptr[Count].Length <= 0 ) 
			tempLine_ptr[Count].Length = sqrtf( powf( (x2-x1), 2) + powf( (y2-y1), 2));

		RendLineList.push_back( &tempLine_ptr[Count] );
	}else{
		std::cout << "Can't create new line, increase number in UFI_lines constructor" << std::endl; 
		exit(1);
	}
}

void UFI_Line::NewLine(SDL_Point A, SDL_Point B, SDL_Color color){
	
	tempLine_ptr[Count].A.x = A.x;
	tempLine_ptr[Count].A.y = A.y;
	tempLine_ptr[Count].B.x = B.x;
	tempLine_ptr[Count].B.y = B.y;
	tempLine_ptr[Count].Color = color;
	tempLine_ptr[Count].Width = 1; //test
	if( tempLine_ptr[Count].Length <= 0 ) tempLine_ptr[Count].Length = sqrtf( powf( (B.x-A.x), 2) + powf( (B.y-A.y), 2));

	this->RendLineList.push_back( &tempLine_ptr[Count] );
	
	Count++;	
}

void UFI_Line::NewLine_Future(SDL_Point A, int Alpha, SDL_Point B, SDL_Color Color){
	SDL_Point tempMid;
	SDL_Point tempDelta;

	float Alpha_rad = (Alpha+15)*3.1415/180; // Whyyyyyy 15 ??????
	float K;
	
	tempDelta.x = fabs(A.x - B.x);
	tempDelta.y = fabs(A.y - B.y);
	
	tempMid.x = A.x + tempDelta.x/2;
	tempMid.y = A.y + tempDelta.y/2;
	
	if( (A.x - B.x) > 0){
		K = (-1)*cos(Alpha_rad);
		tempMid.x = A.x - tempDelta.x/2;
		tempMid.y = A.y - tempDelta.y/2;
	}
	else {
		K = cos(Alpha_rad);
		tempMid.x = A.x + tempDelta.x/2;
		tempMid.y = A.y + tempDelta.y/2;
	}
	
	if( tempDelta.x <= (tempDelta.y*2)) K = K*tempDelta.x/tempDelta.y/2; 
	
		NewLine(A.x, A.y, tempMid.x - tempDelta.y*K, A.y, Color);
		NewLine(tempMid.x - tempDelta.y*K, A.y, tempMid.x + tempDelta.y*K, B.y, Color );
		NewLine(tempMid.x + tempDelta.y*K, B.y, B.x, B.y, Color);
}


void UFI_Line::Display(){
	for (auto it = this->RendLineList.begin(); it != this->RendLineList.end(); ++it)
	{	
		SDL_SetRenderDrawColor( private_Rend, (*it)->Color.r, (*it)->Color.g, (*it)->Color.b, (*it)->Color.a );
		SDL_RenderDrawLine(private_Rend, (*it)->A.x, (*it)->A.y,(*it)->B.x, (*it)->B.y);
			
	}
}

void UFI_Line::LineInit(SDL_Renderer* renderer){
	private_Rend = renderer;
}